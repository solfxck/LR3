package main

import (
	"encoding/gob" // пакет для работы с бинарной сериализацией
	"os"           // пакет для работы с файловой системой
)

// node представляет узел в стеке
type Node struct {
	Data string // данные, хранящиеся в узле
	Next *Node  // указатель на следующий узел в стеке
}

// stack представляет структуру данных "стек"
type Stack struct {
	Top *Node // указатель на верхний элемент стека
}

// newStack создает новый пустой стек
func NewStack() *Stack {
	return &Stack{
		Top: nil, // инициализация стека с пустой вершиной
	}
}

// push добавляет новый элемент на вершину стека
// сложность: O(1)
func (s *Stack) Push(value string) {
	newNode := &Node{
		Data: value, // данные нового узла
		Next: s.Top, // следующий элемент — текущая вершина стека
	}
	s.Top = newNode // обновление вершины стека
}

// pop удаляет верхний элемент из стека
// сложность: O(1)
func (s *Stack) Pop() {
	if s.Top == nil { // проверка, пуст ли стек
		println("Стек пуст!")
		return
	}
	s.Top = s.Top.Next // перемещение вершины на следующий элемент
}

// display выводит все элементы стека
// сложность: O(n), где n — количество элементов в стеке
func (s *Stack) Display() {
	if s.Top == nil { // проверка, пуст ли стек
		println("Стек пуст!")
		return
	}

	current := s.Top // начинаем с вершины стека
	for current != nil {
		print(current.Data, " ") // вывод данных текущего узла
		current = current.Next   // переход к следующему узлу
	}
	println() // перевод строки после вывода всех элементов
}

// getTop возвращает верхний узел стека
func (s *Stack) GetTop() *Node {
	return s.Top // возврат вершины стека
}

// stackData представляет данные для сериализации
type StackData struct {
	Values []string // срез для хранения значений стека
}

// serialize сохраняет стек в бинарный файл
func (s *Stack) Serialize(filename string) error {
	file, err := os.Create(filename) // создаем файл для записи
	if err != nil {
		return err // возвращаем ошибку, если не удалось создать файл
	}
	defer file.Close() // закрываем файл после завершения функции

	// преобразуем стек в срез для сериализации
	var data StackData
	current := s.Top
	for current != nil {
		data.Values = append(data.Values, current.Data) // добавляем данные узла в срез
		current = current.Next                          // переходим к следующему узлу
	}

	// создаем кодировщик и сериализуем данные
	encoder := gob.NewEncoder(file)
	return encoder.Encode(data) // возвращаем ошибку, если сериализация не удалась
}

// deserialize загружает стек из бинарного файла
func (s *Stack) Deserialize(filename string) error {
	file, err := os.Open(filename) // открываем файл для чтения
	if err != nil {
		return err // возвращаем ошибку, если не удалось открыть файл
	}
	defer file.Close() // закрываем файл после завершения функции

	// создаем декодировщик
	decoder := gob.NewDecoder(file)

	// декодируем данные
	var data StackData
	if err := decoder.Decode(&data); err != nil {
		return err // возвращаем ошибку, если декодирование не удалось
	}

	// очищаем текущий стек
	s.Top = nil

	// восстанавливаем стек из загруженных данных (в обратном порядке для сохранения оригинального порядка)
	for i := len(data.Values) - 1; i >= 0; i-- {
		s.Push(data.Values[i]) // добавляем элементы в стек
	}

	return nil // возвращаем nil, если все прошло успешно
}
