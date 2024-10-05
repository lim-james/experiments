#include <algorithm>
#include <iostream>
#include <vector>

template <typename T> class PriorityQueue {
private:
  std::vector<T> arr;

public:
  PriorityQueue() {}

  T peek() { return this->arr[0]; }

  T poll() {
    T result = this->arr[0];
    this->arr[0] = this->arr.back();
    this->arr.pop_back();
    bubbleDown(1);
    return result;
  }

  void offer(T t) {
    size_t i = this->arr.size();
    this->arr.push_back(t);
    bubbleUp(i + 1);
  }

  bool isEmpty() const { return this->arr.empty(); }

  std::vector<T> const &toArray() const { return this->arr; }

private:
  void bubbleUp(size_t i) {
    if (i == 1)
      return;

    size_t pId;

    T &child = this->arr[i - 1];
    T *parent = getParent(i, pId);

    if (child > *parent) {
      std::swap(child, *parent);
      bubbleUp(pId);
    }
  }

  void bubbleDown(size_t i) {
    if (i > (this->arr.size() >> 1))
      return;

    size_t lId, rId;

    T &parent = this->arr[i - 1];
    T *lChild = getLeftChild(i, lId);
    T *rChild = getRightChild(i, rId);

    if (rChild == nullptr) {
      if (*lChild > parent) {
        std::swap(parent, *lChild);
        bubbleDown(lId);
      }
    } else {
      if (*lChild > parent && *rChild > parent) {
        if (*lChild > *rChild) {
          std::swap(parent, *lChild);
          bubbleDown(lId);
        } else {
          std::swap(parent, *rChild);
          bubbleDown(rId);
        }
      } else if (*lChild > parent) {
        std::swap(parent, *lChild);
        bubbleDown(lId);
      } else if (*rChild > parent) {
        std::swap(parent, *rChild);
        bubbleDown(rId);
      }
    }
  }

  T *getParent(size_t i, size_t &id) {
    id = (i >> 1);
    i = id - 1;
    return i < 0 ? nullptr : &this->arr[i];
  }

  T *getLeftChild(size_t i, size_t &id) {
    id = (i << 1);
    i = id - 1;
    return &this->arr[i];
  }

  T *getRightChild(size_t i, size_t &id) {
    i <<= 1;
    id = i | 1;
    return i >= this->arr.size() ? nullptr : &this->arr[i];
  }
};

int main() {
  PriorityQueue<int> pq;
  pq.offer(2);
  pq.offer(6);
  pq.offer(8);
  pq.offer(1);
  pq.offer(0);
  pq.offer(-5);
  pq.offer(4);

  auto arr = pq.toArray();
  for (auto a : arr)
    std::cout << a << ' ';
  std::cout << "\n";

  while (!pq.isEmpty()) {
    std::cout << pq.poll() << '\n';
  }

  return 0;
}
