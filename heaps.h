#pragma once
#include "solutions.h"


void prepMaxHeapArr(Tree<int>* h, std::vector<int>& a) {
	for (size_t i = a.size() / 2; i >= 1; i--) {
		int val = a[i - 1];
		int k = i;
		bool h = false;
		while (!h && k * 2 - 1 < a.size()) {
			int j = k * 2;
			if (j + 1 < a.size()) {		//  + 1 ��� ������ ��������
				if (a[j - 1] < a[j - 1 + 1])		// -1 ��� ����������� ������� (���������� � ����) 
					j = j + 1;
			}
			if (val > a[j - 1])
				h = true;
			else {
				a[k - 1] = a[j - 1];
				k = j;
			}
		}
		a[k - 1] = val;
	}
}

void prepMinHeapArr(Tree<int>* h, std::vector<int>& a) {
	for (size_t i = a.size() / 2; i >= 1; i--) {
		int val = a[i - 1];
		int k = i;
		bool h = false;
		while (!h && k * 2 - 1 < a.size()) {
			int j = k * 2;
			if (j + 1 < a.size()) {		//  + 1 ��� ������ ��������
				if (a[j - 1] > a[j - 1 + 1])		// -1 ��� ����������� ������� (���������� � ����) 
					j = j + 1;
			}
			if (val < a[j - 1])
				h = true;
			else {
				a[k - 1] = a[j - 1];
				k = j;
			}
		}
		a[k - 1] = val;
	}
}

int kthLargestElement(std::vector<int> nums, int k) {
	for (int i = 0; i < nums.size(); i++) {
		for (int j = 0; j < nums.size() - 1; j++) {
			if (nums[j] > nums[j + 1]) {
				nums[j] += nums[j + 1];
				nums[j + 1] = nums[j] - nums[j + 1];
				nums[j] -= nums[j + 1];
			}
		}
	}
	return nums[nums.size() - k];
}

/*Given an absolute file path (Unix-style), shorten it to the format /<dir1>/<dir2>/<dir3>/....

Here is some info on Unix file system paths:

/ is the root directory; the path should always start with it even if it isn't there in the given path;
/ is also used as a directory separator; for example, /code/fights denotes a fights subfolder in the code folder in the root directory;
this also means that // stands for "change the current directory to the current directory"
. is used to mark the current directory;
.. is used to mark the parent directory; if the current directory is root already, .. does nothing.
Example

For path = "/home/a/./x/../b//c/", the output should be
simplifyPath(path) = "/home/a/b/c".

Here is how this path was simplified:
* /./ means "move to the current directory" and can be replaced with a single /;
* /x/../ means "move into directory x and then return back to the parent directory", so it can replaced with a single /;
* // means "move to the current directory" and can be replaced with a single /.*/

void goParendDir(std::string& s, size_t& idx) {
	int seqMax = 2;
	if (idx == 1)
		seqMax = 1;
	size_t seq = 0;
	size_t counter = 1;
	for (;; counter++) {
		if (s[idx] == '/') {
			seq++;
			if (seq == seqMax)
				break;
		}
		--idx;
	}
	s.erase(idx, counter + 1);
}

void checkPath(std::string& s) {
	if (!s.empty() && s.at(0) != '/')
		s.insert(0, 1, '/');
}

std::string simplifyPath(std::string path) {
	if (!path.empty() && path.at(0) != '/')
		path.insert(0, 1, '/');
	for (size_t i = 0; i < path.length() - 1; i++)
		if (path[i] == '/' && path[i + 1] == '/') {
			path.erase(i + 1, 1);
			i--;
		}

	for (size_t i = 0; i < path.length(); i++) {
		char ch = path.at(i);
		if (path.at(i) == '.') {
			if (i + 1 < path.length() && path.at(i + 1) == '.') {
				goParendDir(path, i);
			}
			else if (i + 1 < path.length() && path.at(i + 1) == '/') {
				path.erase(i, 2);
				i = i - 1;
			}
		}
		else if (path.at(i) == '/') {
		}
	}
	if (path.length() != 1 && path.at(path.length() - 1) == '/')
		path.erase(path.length() - 1, 1);
	return path;
}

/*Given an encoded string, return its corresponding decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is repeated exactly k times. Note: k is guaranteed to be a positive integer.

Note that your solution should have linear complexity because this is what you will be asked during an interview.

Example

For s = "4[ab]", the output should be
decodeString(s) = "abababab";

For s = "2[b3[a]]", the output should be
decodeString(s) = "baaabaaa";

For s = "z1[y]zzz2[abc]", the output should be
decodeString(s) = "zyzzzabcabc".*/

void squareBracket(std::string& s, size_t& idx) {
	int counter = 0;
	std::string sDigit;
	for (; idx > 0; idx--) {
		if (std::isdigit(s[idx - 1])) {
			sDigit.insert(0, 1, s[idx - 1]);
		}
		else
			break;
	}
	s.erase(idx, sDigit.length());
	int digit = 1;
	if (!sDigit.empty())
		digit = std::stoi(sDigit);

	size_t mark1 = idx;
	size_t mark2 = mark1;
	size_t seq_squar = 0;
	for (; mark2 < s.length(); mark2++) {
		if (s[mark2] == ']') {
			s.erase(mark2, 1);
			break;
		}
		else if (s[mark2] == '[') {
			seq_squar++;
			if (seq_squar >= 2) {
				squareBracket(s, mark2);
				mark2--;
				continue;
			}
			s.erase(mark2, 1);
			mark2--;
		}
	}
	size_t seek = mark2;
	std::string suf = s.substr(mark1, mark2 - mark1);
	for (size_t i = 0; i < digit - 1; i++) {
		s.insert(seek, suf);
		seek += mark2 - mark1;
	}
}

std::string decodeString(std::string s) {
	for (size_t i = 0; i < s.length(); i++) {
		switch (s[i])
		{
		case '[':
			squareBracket(s, i);
			break;
		default:
			break;
		}
	}
	return s;
}

/*Note: Write a solution with O(n) complexity, since this is what you would be asked to do during a real interview.

Given an array a composed of distinct elements, find the next larger element for each element of the array, i.e. the first element to the right that is greater than this element, in the order in which they appear in the array, and return the results as a new array of the same length. If an element does not have a larger element to its right, put -1 in the appropriate cell of the result array.

Example

For a = [6, 7, 3, 8], the output should be
nextLarger(a) = [7, 8, 8, -1].

In this array, the next larger element for 6 is 7, for 7 is 8, for 3 is 8 (7 is not a valid option since elements from a can only be compared to elements to their right), and for 8 there is no such element, so we put -1 in the last cell.*/

std::vector<int> nextLarger(std::vector<int> a) {
	for (size_t i = 0; i < a.size(); i++) {
		size_t j = i + 1;
		for (; j < a.size(); j++) {
			if (a[i] < a[j]) {
				a[i] = a[j];
				break;
			}
		}

		if (j == a.size())
			a[i] = -1;
	}
	return a;
}

/*Note: Write a solution with O(operations.length) complexity, since this is what you would be asked to do during a real interview.

Implement a modified stack that, in addition to using push and pop operations, allows you to find the current minimum element in the stack by using a min operation.

Example

For operations = ["push 10", "min", "push 5", "min", "push 8", "min", "pop", "min", "pop", "min"], the output should be
minimumOnStack(operations) = [10, 5, 5, 5, 10].

The operations array contains 5 instances of the min operation. The results array contains 5 numbers, each representing the minimum element in the stack at the moment when min was called.*/

class Stack {
public:
	Stack() {};
	struct Node {
		Node(int v) :value(v), next(nullptr) { }
		int value;
		Node* next;
	};
	Node* top = nullptr;
	int min() {
		int min = top->value;
		Node* cur = top;
		while (cur->next != nullptr) {
			cur = cur->next;
			if (min > cur->value)
				min = cur->value;
		}
		return min;
	}
	void push(int value) {
		if (top == nullptr) {
			top = new Node(value);
		}
		else {
			Node* tmp = top;
			top = new Node(value);
			top->next = tmp;
		}
	}
	void pop() {
		Node* tmp = top;
		top = top->next;
		delete tmp;
	}
};

std::vector<int> minimumOnStack(std::vector<std::string> operations) {
	std::vector<int> v;
	Stack stack;
	for (size_t i = 0; i < operations.size(); i++) {
		size_t idx = 0;
		switch (operations[i][1])
		{
		case 'u':
			while (idx + 1 < operations[i].length() && !std::isdigit(operations[i][++idx]));
			stack.push(std::stoi(operations[i].substr(idx, operations[i].size() - idx)));
			break;
		case 'i':
			v.push_back(stack.min());
			break;
		case 'o':
			stack.pop();
			break;
		}
	}
	return v;
}

/*Given a 2D grid skyMap composed of '1's (clouds) and '0's (clear sky), count the number of clouds. A cloud is surrounded by clear sky, and is formed by connecting adjacent clouds horizontally or vertically. You can assume that all four edges of the skyMap are surrounded by clear sky.

Example

For

skyMap = [['0', '1', '1', '0', '1'],
		  ['0', '1', '1', '1', '1'],
		  ['0', '0', '0', '0', '1'],
		  ['1', '0', '0', '1', '1']]
the output should be
countClouds(skyMap) = 2;

For

skyMap = [['0', '1', '0', '0', '1'],
		  ['1', '1', '0', '0', '0'],
		  ['0', '0', '1', '0', '1'],
		  ['0', '0', '1', '1', '0'],
		  ['1', '0', '1', '1', '0']]
the output should be
countClouds(skyMap) = 5.*/

int countClouds(std::vector<std::vector<char>> skyMap) {
	std::stack<std::pair<int, int>> stack;
	size_t counter = 0;
	for (size_t i = 0; i < skyMap.size(); i++) {
		for (size_t j = 0; j < skyMap[i].size(); j++) {
			if (skyMap[i][j] == '1') {
				counter++;
				stack.push({ i,j });
				while (!stack.empty()) {
					auto [y, x] = stack.top();
					stack.pop();
					skyMap[y][x] = '0';
					if (x + 1 < skyMap[y].size() && skyMap[y][x + 1] == '1')
						stack.push({ y, x + 1 });
					if (x - 1 >= 0 && skyMap[y][x - 1] == '1')
						stack.push({ y, x - 1 });
					if (y + 1 < skyMap.size() && skyMap[y + 1][x] == '1')
						stack.push({ y + 1, x });
					if (y - 1 >= 0 && skyMap[y - 1][x] == '1')
						stack.push({ y - 1, x });
				}
			}
		}
	}
	return counter;
}

/*Given an array of integers a, return a new array b using the following guidelines:

For each index i in b, the value of bi is the index of the aj nearest to ai and is also greater than ai.
If there are two options for bi, put the leftmost one in bi.
If there are no options for bi, put -1 in bi.
Example

For a = [1, 4, 2, 1, 7, 6], the output should be
nearestGreater(a) = [1, 4, 1, 2, -1, 4].

for a[0], the nearest larger element is 4 at index a[1] -> b[0] contains the value 1.
for a[1], the nearest larger element is 7 at a[4] -> b[1] contains the value 4.
for a[2], the nearest larger element is 4 at a[1] (7 is also larger, but 4 has the minimal position) -> b[2] contains the value 1.
for a[3], the nearest larger element is 2 at a[2] (7 is also larger, but 2 has the minimal position) -> b[3] contains the value 2.
for a[4], there is no element larger than 7 -> b[4] contains the value -1.
for a[5], the nearest larger element is 7 at a[4] -> b[5] contains the value 4.*/

std::vector<int> nearestGreater(std::vector<int> a) {
	std::vector<int> b(a.size());
	for (int i = 0; i < a.size(); i++) {
		bool check = false;
		int cnt = 1;
		bool lastCheck = true;
		while (!check) {
			if (i - cnt >= 0 && a[i - cnt] > a[i]) {
				b[i] = i - cnt;
				check = true;
			}
			else if (i + cnt < a.size() && a[i + cnt] > a[i]) {
				b[i] = i + cnt;
				check = true;
			}
			else if (i + cnt >= a.size() && i - cnt < 0) {
				b[i] = -1;
				break;
			}
			if (lastCheck && i - 1 >= 0) {
				if (a[i] >= a[i - 1]) {
					int lastIdx = b[i - 1];
					int diff = 0;
					if (lastIdx > i - 1) {
						diff = lastIdx - i - 1;
					}
					else {
						diff = i - 1 - lastIdx;
					}
					if (diff > 2)
						cnt = diff - 1;
				}
				lastCheck = false;
			}
			cnt++;
		}
	}
	return b;
}

void testHeaps() {
	std::vector<int> v1{ 58, 477, 371, 149, 185, 8, 66, 325, 325, 378, 341, 450, 92, 143, 398, 480, 96, 451, 310, 246, 129, 77, 260, 491, 30, 142, 286, 401, 382, 364, 475, 496, 370, 334, 114, 276, 253, 407, 76, 106, 55, 48, 198, 295, 400, 89, 414, 168, 417, 172 };
	std::vector<int> v2 = nearestGreater(v1);
	for (size_t i = 0; i < v2.size(); i++) {
		std::cout << v2[i] << " ";
	}

	//	std::cout << countClouds({ {
	//'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'
	//		} });
	//

		//std::vector<std::string> v1{ "push 538580174","min", "push 120004347", "min", "pop", "min", "pop", "push 791405182", "min", "pop", "push 336848461", "min", "pop", "push 279001335", "min", "push 594354012", "min" };
		//std::vector<int> v2 = minimumOnStack(v1);
		//for (size_t i = 0; i < v2.size(); i++) 
		//	std::cout << v2[i] << " ";


		//std::vector<int> v1{ 10, 3, 12, 4, 2, 9, 13, 0, 8, 11, 1, 7, 5, 6 };
		//std::vector v2 = nextLarger(v1);
		//for (size_t i = 0; i < v2.size(); i++) {
		//	std::cout << v2[i] << " ";
		//}

		//std::cout << decodeString("2[20[bc]31[xy]]xd4[rt]") << std::endl;

		//std::cout << simplifyPath("folder/subfolder/subsubfolder/.//../anotherfolder/file.txt");

		//std::cout << kthLargestElement({ 7, 6, 5, 4, 3, 2, 1 }, 2);
}