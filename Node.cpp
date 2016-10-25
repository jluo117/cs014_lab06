#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

Node::Node(string data) : data(data), left(0), right(0), parent(0) {}