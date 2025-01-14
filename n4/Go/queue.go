package main

import (
	"bufio"      // пакет для буферизованного ввода-вывода
	"encoding/gob" // пакет для работы с бинарной сериализацией
	"os"         // пакет для работы с файловой системой
	"strings"    // пакет для работы со строками
)

// Node представляет узел в очереди
type Node struct {
	Data string // данные, хранящиеся в узле
	Next *Node  // указатель на следующий узел в очереди
}

// Queue представляет структуру данных "очередь"
type Queue struct {
	Head *Node // указатель на первый элемент очереди
	Tail *Node // указатель на последний элемент очереди
}

// NewQueue создает новую пустую очередь
func NewQueue() *Queue {
	return &Queue{
		Head: nil, // инициализация очереди с пустой головой
		Tail: nil, // инициализация очереди с пустым хвостом
	}
}

// Push добавляет новый элемент в конец очереди
// сложность: O(1)
func (q *Queue) Push(value string) {
	newNode := &Node{
		Data: value, // данные нового узла
		Next: nil,   // следующий элемент всегда nil, так как добавляем в конец
	}

	if q.Head == nil { // если очередь пуста
		q.Head = newNode // новый узел становится головой
		q.Tail = newNode // и хвостом
	} else {
		q.Tail.Next = newNode // добавляем новый узел после текущего хвоста
		q.Tail = newNode      // обновляем хвост
	}
}

// Pop удаляет первый элемент из очереди
// сложность: O(1)
func (q *Queue) Pop() {
	if q.Head == nil { // проверка, пуста ли очередь
		println("Очередь пуста!")
		return
	}

	q.Head = q.Head.Next // перемещение головы на следующий элемент

	if q.Head == nil { // если очередь стала пустой
		q.Tail = nil // обнуляем и хвост
	}
}

// Display выводит все элементы очереди
// сложность: O(n), где n — количество элементов в очереди
func (q *Queue) Display() {
	if q.Head == nil { // проверка, пуста ли очередь
		println("Очередь пуста!")
		return
	}

	current := q.Head // начинаем с головы очереди
	for current != nil {
		print(current.Data, " ") // вывод данных текущего узла
		current = current.Next   // переход к следующему узлу
	}
	println() // перевод строки после вывода всех элементов
}

// GetHead возвращает первый узел очереди
func (q *Queue) GetHead() *Node {
	return q.Head
}

// GetTail возвращает последний узел очереди
func (q *Queue) GetTail() *Node {
	return q.Tail
}

// QueueData представляет данные для сериализации
type QueueData struct {
	Values []string // срез для хранения значений очереди
}

// Serialize сохраняет очередь в бинарный файл
func (q *Queue) Serialize(filename string) error {
	file, err := os.Create(filename) // создаем файл для записи
	if err != nil {
		return err // возвращаем ошибку, если не удалось создать файл
	}
	defer file.Close() // закрываем файл после завершения функции

	// преобразуем очередь в срез для сериализации
	var data QueueData
	current := q.Head
	for current != nil {
		data.Values = append(data.Values, current.Data) // добавляем данные узла в срез
		current = current.Next                          // переходим к следующему узлу
	}

	// создаем кодировщик и сериализуем данные
	encoder := gob.NewEncoder(file)
	return encoder.Encode(data) // возвращаем ошибку, если сериализация не удалась
}

// Deserialize загружает очередь из бинарного файла
func (q *Queue) Deserialize(filename string) error {
	file, err := os.Open(filename) // открываем файл для чтения
	if err != nil {
		return err // возвращаем ошибку, если не удалось открыть файл
	}
	defer file.Close() // закрываем файл после завершения функции

	// создаем декодировщик
	decoder := gob.NewDecoder(file)

	// декодируем данные
	var data QueueData
	if err := decoder.Decode(&data); err != nil {
		return err // возвращаем ошибку, если декодирование не удалось
	}

	// очищаем текущую очередь
	q.Head = nil
	q.Tail = nil

	// восстанавливаем очередь из загруженных данных
	for _, value := range data.Values {
		q.Push(value) // добавляем элементы в очередь
	}

	return nil // возвращаем nil, если все прошло успешно
}

// SerializeText сохраняет очередь в текстовый файл
// каждый элемент записывается в отдельной строке
func (q *Queue) SerializeText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	current := q.Head
	for current != nil {
		_, err := writer.WriteString(current.Data + "\n")
		if err != nil {
			return err
		}
		current = current.Next
	}

	return writer.Flush()
}

// DeserializeText загружает очередь из текстового файла
// каждая строка считается отдельным элементом
func (q *Queue) DeserializeText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// очищаем текущую очередь
	q.Head = nil
	q.Tail = nil

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		// удаляем пробелы в начале и конце строки
		value := strings.TrimSpace(scanner.Text())
		if value != "" { // пропускаем пустые строки
			q.Push(value)
		}
	}

	return scanner.Err()
}
