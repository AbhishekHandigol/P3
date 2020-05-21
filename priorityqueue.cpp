#include <iostream>
#include <cmath>
#include "json.hpp"

#include "priorityqueue.h"
/* Parent is at i/2
left child is at i*2
Right at i*2+1*/



PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
   if (size() == max_size_) {
        return;
   }
   size_++;
   nodes_[size_] = kv;
   heapifyUp(size());
}

KeyValuePair PriorityQueue::min() {
    return nodes_.at(1);
}

void PriorityQueue::removeMin() {
    removeNode(1);
}

bool PriorityQueue::isEmpty() const {
	if (size_) {
        return false;
	}
    return true;
}

size_t PriorityQueue::size() const {
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    if ((i != 1) && (getKey(i) < getKey(i/2))) {
        nodes_.at(i).swap(nodes_.at(i/2));
        heapifyUp(i/2);
    }
}

void PriorityQueue::heapifyDown(size_t i) {
    if (i >= (floor(size_/2.00)+1)) {
        return;
    }
    auto minchild = (getKey(i*2) <= getKey(i*2+1) ? i*2 : i*2+1);
    if (getKey(i*2) == 0) {
        minchild = i*2+1;
    }
    if (getKey(i*2+1) == 0) {
        minchild = i*2;
    }
    if ((getKey(i) > getKey(minchild)) && (getKey(minchild) != 0)) {
        nodes_.at(i).swap(nodes_.at(minchild));
        heapifyDown(minchild);
    }
}

void PriorityQueue::removeNode(size_t i) {
	nodes_.at(i).swap(nodes_.at(size()));
	nodes_.at(size()).first = 0;
	size_--;
	heapifyDown(i);
}

std::vector<KeyValuePair> PriorityQueue::getNodes(){
    return nodes_;
};

Key PriorityQueue::getKey(size_t i) {
    return nodes_.at(i).first;
}
