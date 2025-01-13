package main

// node представляет узел в стеке
type Node struct {
	data string // данные, хранящиеся в узле
	next *Node  // указатель на следующий узел в стеке
}

// stack представляет структуру данных "стек"
type Stack struct {
	top *Node // указатель на верхний элемент стека
}

// newStack создает новый пустой стек
func NewStack() *Stack {
	return &Stack{
		top: nil, // инициализация стека с пустым верхним элементом
	}
}

// push добавляет новый элемент на вершину стека
// сложность: O(1)
func (s *Stack) Push(value string) {
	newNode := &Node{
		data: value, // данные нового узла
		next: s.top, // следующий элемент — текущая вершина стека
	}
	s.top = newNode // обновление вершины стека
}

// pop удаляет верхний элемент из стека
// сложность: O(1)
func (s *Stack) Pop() {
	if s.top == nil { // проверка, пуст ли стек
		println("Стек пуст!")
		return
	}
	s.top = s.top.next // перемещение вершины на следующий элемент
}

// display выводит все элементы стека
// сложность: O(n), где n — количество элементов в стеке
func (s *Stack) Display() {
	if s.top == nil { // проверка, пуст ли стек
		println("Стек пуст!")
		return
	}

	current := s.top // начинаем с вершины стека
	for current != nil {
		print(current.data, " ") // вывод данных текущего узла
		current = current.next   // переход к следующему узлу
	}
	println() // перевод строки после вывода всех элементов
}

// getTop возвращает верхний узел стека
func (s *Stack) GetTop() *Node {
	return s.top // возврат вершины стека
}
