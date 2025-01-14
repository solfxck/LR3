package main

import (
	"os"
	"testing"
)

// TestNewQueue тестирует создание новой очереди
func TestNewQueue(t *testing.T) {
	queue := NewQueue()
	if queue == nil {
		t.Error("Ожидалось, что очередь будет создана, но получено nil")
	}
	if queue.head != nil || queue.tail != nil {
		t.Error("Ожидалось, что пустая очередь будет иметь nil в голове и хвосте")
	}
}

// TestPush тестирует добавление элементов в очередь
func TestPush(t *testing.T) {
	tests := []struct {
		name     string   // название теста
		values   []string // значения для добавления в очередь
		expected []string // ожидаемые значения в очереди (в порядке от головы)
	}{
		{
			name:     "Добавление одного значения",
			values:   []string{"a"},
			expected: []string{"a"},
		},
		{
			name:     "Добавление нескольких значений",
			values:   []string{"a", "b", "c"},
			expected: []string{"a", "b", "c"}, // очередь работает по принципу FIFO (первый вошел, первый вышел)
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			queue := NewQueue()
			for _, v := range tt.values {
				queue.Push(v)
			}

			current := queue.GetHead()
			for i, expected := range tt.expected {
				if current == nil {
					t.Errorf("Ожидалось значение на позиции %d, но получено nil", i)
					return
				}
				if current.data != expected {
					t.Errorf("Ожидалось %s на позиции %d, но получено %s", expected, i, current.data)
				}
				current = current.next
			}
		})
	}
}

// TestPop тестирует удаление элементов из очереди
func TestPop(t *testing.T) {
	tests := []struct {
		name          string   // название теста
		setupValues   []string // значения для добавления в очередь перед тестом
		popCount      int      // количество удалений из очереди
		expectedHead  string   // ожидаемое значение в голове очереди после удалений
		expectedEmpty bool     // ожидается ли пустая очередь после удалений
	}{
		{
			name:          "Удаление из пустой очереди",
			setupValues:   []string{},
			popCount:      1,
			expectedEmpty: true,
		},
		{
			name:          "Удаление одного значения",
			setupValues:   []string{"a", "b"},
			popCount:      1,
			expectedHead:  "b",
			expectedEmpty: false,
		},
		{
			name:          "Удаление нескольких значений",
			setupValues:   []string{"a", "b", "c"},
			popCount:      2,
			expectedHead:  "c",
			expectedEmpty: false,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			queue := NewQueue()
			for _, v := range tt.setupValues {
				queue.Push(v)
			}

			for i := 0; i < tt.popCount; i++ {
				queue.Pop()
			}

			if tt.expectedEmpty {
				if queue.GetHead() != nil {
					t.Error("Ожидалась пустая очередь, но получена непустая")
				}
			} else {
				if queue.GetHead() == nil {
					t.Error("Ожидалась непустая очередь, но получена пустая")
				} else if queue.GetHead().data != tt.expectedHead {
					t.Errorf("Ожидалось значение %s в голове, но получено %s", tt.expectedHead, queue.GetHead().data)
				}
			}
		})
	}
}

// TestDisplay тестирует функцию отображения содержимого очереди
func TestDisplay(t *testing.T) {
	queue := NewQueue()

	// тестируем пустую очередь
	queue.Display() // должно вывести "Очередь пуста!"

	// тестируем очередь с элементами
	values := []string{"a", "b", "c"}
	for _, v := range values {
		queue.Push(v)
	}
	queue.Display() // должно вывести "a b c"
}

// TestFileOperations тестирует операции с файлами
func TestFileOperations(t *testing.T) {
	queue := NewQueue()
	testFile := "test_queue.txt"

	// тест сохранения пустой очереди
	err := saveQueueToFile(queue, testFile)
	if err != nil {
		t.Errorf("Не удалось сохранить пустую очередь: %v", err)
	}

	// тест загрузки из пустого файла
	err = loadQueueFromFile(queue, testFile)
	if err != nil {
		t.Errorf("Не удалось загрузить из пустого файла: %v", err)
	}

	// тест с данными
	testData := []string{"first", "second", "third"}
	for _, data := range testData {
		queue.Push(data)
	}

	// сохранение
	err = saveQueueToFile(queue, testFile)
	if err != nil {
		t.Errorf("Не удалось сохранить очередь в файл: %v", err)
	}

	// загрузка в новую очередь
	newQueue := NewQueue()
	err = loadQueueFromFile(newQueue, testFile)
	if err != nil {
		t.Errorf("Не удалось загрузить очередь из файла: %v", err)
	}

	// проверка данных
	current1 := queue.GetHead()
	current2 := newQueue.GetHead()
	for i := 0; current1 != nil && current2 != nil; i++ {
		if current1.data != current2.data {
			t.Errorf("Несоответствие данных на позиции %d: ожидалось %s, получено %s",
				i, current1.data, current2.data)
		}
		current1 = current1.next
		current2 = current2.next
	}

	if current1 != nil || current2 != nil {
		t.Error("Очереди имеют разную длину")
	}

	// очистка
	os.Remove(testFile)
}

// BenchmarkPush тестирует производительность операции Push
func BenchmarkPush(b *testing.B) {
	queue := NewQueue()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		queue.Push("test")
	}
}

// BenchmarkPop тестирует производительность операции Pop
func BenchmarkPop(b *testing.B) {
	queue := NewQueue()
	// подготовка: добавляем 1000 элементов в очередь
	for i := 0; i < 1000; i++ {
		queue.Push("test")
	}

	b.ResetTimer()
	for i := 0; i < b.N && queue.GetHead() != nil; i++ {
		queue.Pop()
	}
}

// BenchmarkPushPop тестирует производительность чередующихся операций Push и Pop
func BenchmarkPushPop(b *testing.B) {
	queue := NewQueue()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		queue.Push("test")
		if queue.GetHead() != nil {
			queue.Pop()
		}
	}
}
