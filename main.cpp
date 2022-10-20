#include <iostream>
#include <vector>
#include <ctime>

enum {
    POSITIVE,
    NEGATIVE,
    MIX
};

template <class T>
void Swap(T& first, T& second){
    T* temp = new T;
    *temp = first;
    first = second;
    second = *temp;
    delete temp;
};

template <class T>
void ShowArray(T array[], int size){
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
void FillArray(T array[], int size, int type = 0){
    if (size < 0){
        std::cout << "Error negative size!" << std::endl;
        return;
    }
    if (type == POSITIVE){
        for (int i = 0; i < size; ++i) {
            array[i] = rand()%100;
        }
    }
    if (type == NEGATIVE){
        for (int i = 0; i < size; ++i) {
            array[i] = (rand()%100)*(-1);
        }
    }
    if (type == MIX){
        for (int i = 0; i < size; ++i) {
            if(i%2){
                array[i] = rand()%100;
            } else{
                array[i] = (rand()%100)*(-1);
            }
        }
    }
}

template <class T>
void ClearArray (T array[], int size){
    if (size < 0){
        std::cout << "Error negative size!" << std::endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        array[i] = 0;
    }
}

template <class T>
void Heapify(T array[], int size, int current = 0){
    if (size < 0){
        std::cout << "Error negative size!" << std::endl;
        return;
    }
    int largest = current; // Объявляем переменную для индекса наибольшего элемента, по умолчанию это корневой элемент.
    int left = 2*current +1; // Объявляем левого и правого потомков
    int right = 2*current +2;
    // Проверка на наибольшее число в поддереве.
    if (left < size && array[left] > array[largest]){ // Так как мы можем рекурсивно зайти в элемент без потомков, устонавливаем в условии
        largest = left;//- что индекс левого и правого потомка, не выходят за рамки массива.
    }
    if (right < size && array[right] > array[largest]){
        largest = right;
    }
    // Если индекс наибольшего элемента, не соответствует корневому то меняем их местами.
    if (largest != current){
        Swap(array[largest], array[current]);
        // Так как после замены, предыдущий корневой элемент может стать корневым элементом для дерева уровнем ниже, необходимо проверить
        // Будет ли это дерево соответствовать свойству кучи.
        // Для этого вызываем функцию рекурсивно указывая индекс по которому лежал наибольший элемент в качестве текущего(корневого) для дерева уровнем ниже.
        // Когда рекурсия дойдёт до дерева без потомков, условия которые могли бы изменить значение наибольшего элемена не выполняться,
        // Так как индекс таких потомков будет превышать размер массива, следовательно и условие запускающее дальнейшую рекурсию не выполниться.
        // Так как функция ничего не возвращает, то после выполнения посленей проверки, она завершиться и закроет все рекурсивно вызванные функции перед собой.
        Heapify(array,size,largest);
    }
};

template <class T>
void MakeHeap(T array[], int size){
    if (size < 0){
        std::cout << "Error negative size!" << std::endl;
        return;
    }
    // Для создании кучи, нужно применить функцию восстановления свойств кучи для каждого элемента кучи, имеющего потомков.
    // Так как куча двоичная, то потомко будут иметь только элементы начиная с её середины, а поскольку массив начинается с нуля, то необходимо также уменьшить размер на 1.
    for (int i = (size/2) -1; i >= 0; --i) {
        Heapify(array,size,i);
    }
};

template <class T>
void SortHeap(T array[], int size){
    if (size < 0){
        std::cout << "Error negative size!" << std::endl;
        return;
    }
    // Принцип сортировки - Так как убывающей куче корневой элемент является наибольшим то можно провести сортировку поменяв его местами
    // с последним элементом массива, а затем вызвав функцию восстановления свойств кучи, с размером массива на единицу меньше.
    // Таким образом необходимо пройти по всему массиву, в процессе сортировки, левая часть массива будет представлять из себя кучу, а правая отсортированный по возрастанию массив.
    // Так как цикл for - линейный а Heapify выполняется логарифмически, то при сортировке идеального бинарного дерева, сортировка будет выполняться за n*log(n).
    for (int i = size-1; i >= 0 ; --i) {
        Swap(array[0],array[i]);
        Heapify(array,i,0);
    }
};

template <class T>
void Test (int size){
    T *array = new T[size];
    for (int i = 0; i < 3; ++i) {
        std::cout << "Start test with :" << size;
        if (i == POSITIVE){
            std::cout << " POZITIVE elements" << std::endl;
        }
        if (i == NEGATIVE){
            std::cout << " NEGATIVE elements" << std::endl;
        }
        if (i == MIX){
            std::cout << " MIX elements" << std::endl;
        }

        FillArray(array,size,i);
        ShowArray(array, size);
        std::cout << "Make a heap" << std::endl;
        MakeHeap(array,size);
        ShowArray(array,size);
        std::cout << "Sort Heap: " << std::endl;
        SortHeap(array,size);
        ShowArray(array,size);
        std::cout << "Finish Test: " << std::endl << std::endl;
        ClearArray(array,size);
    }
    delete[] array;
}

int main() {
    srand(time(NULL));
    int size;
    //Test ZERO elements;
    size = 0;
    Test<int>(size);

    //Test one element;
    size = 1;
    Test<int>(size);

    //Test two elements;
    size = 2;
    Test<int>(size);

    //Test three elements;
    size = 3;
    Test<int>(size);

    //Test 5 elements;
    size = 5;
    Test<int>(size);

    //Test 10 elements;
    size = 10;
    Test<int>(size);

    //Test 50 elements;
    size = 50;
    Test<int>(size);

    //Test 100 elements;
    size = 100;
    Test<int>(size);

}
