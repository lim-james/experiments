# Dynamic Dispatch

I was once asked to describe the virtual keyword in cpp during an interview, and
embarassingly I described it wrongly. Well now I know that without `virtual`,
C++ does not assume dynamic dispatch. And one other thing I find interesting
which I want to test is that by introducing dyanmic dispatch we add an overhead
of size because the class has to point to the v-table.
