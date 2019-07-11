//Реализация основана на создании класса двоичной кучи. Функция добавления элемента в кучу устроена так,
//что добавляются только уникальные элементы. Реализованы методы siftUp и siftDown(в программе не используется,
//но может пригодиться при доработках). Выход из программы осуществляется при вводе символа q в консоли.
#include <iostream>
#include <algorithm>

#define DEFAULT_HEAP_SIZE 8
#define HAPPY_NUMBER 6

class ticketHeap {
private:
	int size;
	int heapSize;
	int* heap;
	void siftUp(int);
	void siftDown(int);
	int add(int);//Смотрит, есть ли элемент в куче и если не находит - добавляет. Возвращает 0, если билет встретился впервые, 1 - если уже встречался
	int checkSums(int);//проверяет сумму цифр числа
	int searchNum(int);
public:
	ticketHeap() {
		this->size = DEFAULT_HEAP_SIZE;
		this->heapSize = 0;
		this->heap = new int[size];
	}
	~ticketHeap() {
		delete []this->heap;
		size = 0;
		heapSize = 0;
	};
	int checkHappy(int);//Проверяет - счастливый билет или нет. Сначала проверяется сумма цифр, после чего пытаемся добавить номер в кучу при помощи add
};

void ticketHeap::siftUp(int i) {//Просеивание вверх, нужно для добавления в кучу
	while (this->heap[i] < this->heap[(i - 1) / 2]) {
		std::swap(this->heap[i], this->heap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void ticketHeap::siftDown(int i) {
	while (2*i+1 < this->heapSize) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int j;
		j = left;
		if (right < this->heapSize and this->heap[right] < this->heap[left])
			j = right;
		if (this->heap[i] <= this->heap[j])
			break;
		std::swap(this->heap[i], this->heap[j]);
		i = j;
	}
}

int ticketHeap::searchNum(int num) {
	int i = 0;
	while (2 * i + 1 <= this->heapSize) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int j = left; 
		if (right < this->heapSize and this->heap[right] < this->heap[left])
			j = right;
		if (this->heap[i] == num) {
			return 1;
		}
		i = j;
	}
	return 0;
}

int ticketHeap::add(int num) {
	if (!searchNum(num)) {
		this->heapSize = this->heapSize + 1;
		this->heap[this->heapSize - 1] = num;
		siftUp(this->heapSize - 1);
		if (this->heapSize == this->size) {//TODO: вынести выделение памяти в отдельную функцию
			int* tmp;
			tmp = new int[2 * DEFAULT_HEAP_SIZE];
			for (int i = 0; i < this->heapSize; i++) {
				tmp[i] = this->heap[i];
			}
			delete []this->heap;
			this->heap = tmp;
		}
		return 0;
	}
	return 1;
}

int getSumOfNumbers(int num) {//Возвращает количество цифр в числе
	int count = 0;
	while (num / 10 != 0) {
		num = num / 10;
		count++;
	}
	return count;
}

int ticketHeap::checkSums(int num) {//Проверка суммы цифр
	int left = 0; 
	int right = getSumOfNumbers(num);
	int sumLeft = 0;
	int sumRight = 0;
	if (right != HAPPY_NUMBER - 1) {
		return 0;
	}
	while (left < right) {
		int numLeft = (num / (int)std::pow(10, right - left));
		int numRight = (num % 10);
		sumLeft += numLeft;
		sumRight += numRight;
		num = (num - numLeft * (int)std::pow(10, (right-left))) / 10;
		left++;
		right--;
	}
	if (sumLeft == sumRight) {
		return 1;
	}
	else {
		return 0;
	}
}


int ticketHeap::checkHappy(int num) {//проверка "счастливости" билета
	if (checkSums(num)) {
		int selector = add(num);
		if (selector == 0)
			std::cout << "its happy\n";
		else
			std::cout << "its double happy\n";
		return 1;
	}
	std::cout << "its not happy\n";
	return 0;
}


int main() {
	int x = 0;
	ticketHeap one;
	while (std::cin >> x) {
		if (x == 'q')
			break;
		one.checkHappy(x);
	}
	return 0;
}