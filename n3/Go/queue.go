package main

import "fmt"

// Node представляет узел в очереди
type Node struct {
	data string
	next *Node
}

// Queue представляет структуру данных очереди
type Queue struct {
	head *Node
	tail *Node
}

// NewQueue создает новую пустую очередь
func NewQueue() *Queue {
	return &Queue{
		head: nil,
		tail: nil,
	}
}

// GetHead возвращает головной узел очереди
func (q *Queue) GetHead() *Node {
	return q.head
}

// GetTail возвращает хвостовой узел очереди
func (q *Queue) GetTail() *Node {
	return q.tail
}

// Push добавляет новый элемент в конец очереди
// Временная сложность: O(1)
func (q *Queue) Push(value string) {
	node := &Node{data: value, next: nil}

	if q.head == nil {
		// Если очередь пуста, то и голова, и хвост указывают на новый узел
		q.head = node
		q.tail = node
	} else {
		// Добавляем новый узел в конец очереди
		q.tail.next = node
		q.tail = node
	}
}

// Pop удаляет первый элемент из очереди
// Временная сложность: O(1)
func (q *Queue) Pop() {
	if q.head == nil {
		fmt.Println("Очередь пуста!")
		return
	}

	// Перемещаем указатель головы на следующий узел
	q.head = q.head.next

	// Если после удаления очередь стала пустой
	if q.head == nil {
		q.tail = nil
	}
}

// Display выводит все элементы в очереди
// Временная сложность: O(n)
func (q *Queue) Display() {
	if q.head == nil {
		fmt.Println("Очередь пуста!")
		return
	}

	current := q.head
	for current != nil {
		fmt.Printf("%s ", current.data)
		current = current.next
	}
	fmt.Println()
}
