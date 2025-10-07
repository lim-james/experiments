# Thread Pinning

## Pre-exercise thoughts 
> This is subject to error as they are my raw initial thoughts, through the
> experiment I intend to correct and solidify my understanding.

### Premise - context that leads to the problem 
Operating Systems are designed for **fairness**. Naturally, in order to
faciliate concurrency, the scheduler rotates what tasks is active. 

### Problem
This incurs unexpected latency because 
1. we don't have control over it 
2. rotating tasks involves **context switches**, 
3. which incurs costs because context switches flushes the cache and this leads
   to more **cache misses**

### Solutions
I'm aware that there are 2 ways of overcoming this
1. **Pinning threads** to cores so they are never swapped out 
2. Giving tasks a **higher priority** (_niceness?_ - heard about it, time to
   look it up)

## What this experiement is for

I want to see how bad these latencies can be. And I would also like to
practically try out thread pinning as well as setting tasks priority 

## Planning and thoughts 

This is my first proper time writing an OS experiment, so I'm writing out my
thoughts of what needs to be done.

I want to see the scheduler swap my process out unexpectedly, so my program
should be computing something heavy that takes at least a few seconds (I'm not
sure how long is good before I see noticeable differences). And I would run that
naively once, and the second time with thread pinning or priority to compare. I
would need to simulate a busy system so that the scheduler wants to reschedule
my program.

I will be using perf to time my program and also htop to see the resources
that are being used

### The Process

[Python does not support CPU affinity directly](https://sorami-chi.hateblo.jp/entry/2016/04/29/000000) 
I'm wondering why? I know will probably sound stupid in the future, but I rather
sound stupid here than on the job or worse the interview.

[2017 StackOverflow talking about macOS and Thread Affinity](https://stackoverflow.com/questions/42658331/python-3-on-macos-how-to-set-process-affinity)
The answer provided here stats that OSX does not support Thread Affinity. But
this is also 2017..

[Apple's documentation on Thread Affinity API](https://developer.apple.com/library/archive/releasenotes/Performance/RN-AffinityAPI/)
> To support this, two new APIs are introduced in Leopard:
> * A mechanism for an application to express thread affinity hints to the 
>   scheduler as an extension to Mach thread policies.
> * A more uniform and complete set of sysctl(3) controls to obtain processor 
>   cache sharing information.
Seems like there's support now

[Just a fun read on someone asking on this topic](https://discussions.apple.com/thread/252525908?sortBy=rank)


BREAKTHROUGH - Ok I have found a pretty comprehensive python package [psutil](https://psutil.readthedocs.io/en/latest/index.html#process-class)
It has a method [`cpu_affinity`](https://psutil.readthedocs.io/en/latest/index.html#process-class)
, but unfortunately it states this 'Availability: Linux, Windows, FreeBSD'

## Findings

I hit a deadend with attempting to pin my thread on my MacOS. But hey, I learnt
that OSX doesn't have such support for intentional reasons. Nonetheless, that
didn't stop me from seeking the facts instead of figuring out how to pin
threads, I pivoted this experiment to 
1. See context switches happen on a busy system 
2. See the latency that was a result of that

```py
fib of 200000 took 0.52357s
num of ctx switches: pctxsw(voluntary=247, involuntary=0)

fib of 200000 took 0.48892s
num of ctx switches: pctxsw(voluntary=85, involuntary=0)

fib of 200000 took 0.49335s
num of ctx switches: pctxsw(voluntary=30, involuntary=0)
```
Upon looking at these figure, it didn't make sense at all. the 247 to 85 was
valid, but the 85 to 30 looked off. So what's up? what am I missing? Ok
I have a fundamental misunderstanding here - context switches are not the
same as thread migration. Context switch stays within the same thread
which _may_ still have access to its initial cache. Whereas, if an entire
thread is migrated to a totally different core then that's an issue.
Because it's memory space is shifted. Likely with the nature of my program
too, since I am using a bottom-up fib approach, its literally accessing
memory contiguously, so that's too efficient. I need to have more random memory access and also a more cache bulky stresser.

### Figuring out a large enough dataset

```zsh
sysctl hw.l1dcachesize hw.l2cachesize
hw.l1dcachesize: 65536 
hw.l2cachesize: 4194304
```

Upon stressing this I have found some pretty interesting results 

```py
populating 798720 elements
MEM < L1d
3000000 random access took 0.23327s

L1d < MEM < L2
3000000 random access took 0.22637s

L1d + L2 < MEM
3000000 random access took 0.40225s
```

Anything outside of the L1 and L2 cache is defintely taking more time, but
now I'm left wondering why the L1 cache is performing slower than my L2 cache
stress.

## Terms to commit to memory

PID - Process ID
Thread/CPU/Cache Affinity
l1d - L1 Data Cache
l1i - L1 Instruction Cache
