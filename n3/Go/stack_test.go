package main

import (
	"testing"
)

// testNewStack тестирует создание нового стека
func TestNewStack(t *testing.T) {
	stack := NewStack() // создаем новый стек
	if stack == nil {
		t.Error("Ожидалось, что стек будет создан, но получено nil")
	}
	if stack.top != nil {
		t.Error("Ожидалось, что пустой стек будет иметь nil в вершине")
	}
}

// testPush тестирует добавление элементов в стек
func TestPush(t *testing.T) {
	// определяем тестовые случаи
	tests := []struct {
		name     string   // название теста
		values   []string // значения для добавления в стек
		expected []string // ожидаемые значения в стеке (в порядке от вершины)
	}{
		{
			name:     "Добавление одного значения",
			values:   []string{"a"},
			expected: []string{"a"},
		},
		{
			name:     "Добавление нескольких значений",
			values:   []string{"a", "b", "c"},
			expected: []string{"c", "b", "a"}, // стек работает по принципу LIFO (последний вошел, первый вышел)
		},
	}

	// проходим по всем тестовым случаям
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			stack := NewStack() // создаем новый стек для каждого теста
			for _, v := range tt.values {
				stack.Push(v) // добавляем значения в стек
			}

			// проверяем значения в стеке
			current := stack.GetTop() // начинаем с вершины стека
			for i, expected := range tt.expected {
				if current == nil {
					t.Errorf("Ожидалось значение на позиции %d, но получено nil", i)
					return
				}
				if current.data != expected {
					t.Errorf("Ожидалось %s на позиции %d, но получено %s", expected, i, current.data)
				}
				current = current.next // переходим к следующему узлу
			}
		})
	}
}

// testPop тестирует удаление элементов из стека
func TestPop(t *testing.T) {
	// определяем тестовые случаи
	tests := []struct {
		name          string   // название теста
		setupValues   []string // значения для добавления в стек перед тестом
		popCount      int      // количество удалений из стека
		expectedTop   string   // ожидаемое значение на вершине стека после удалений
		expectedEmpty bool     // ожидается ли пустой стек после удалений
	}{
		{
			name:          "Удаление из пустого стека",
			setupValues:   []string{},
			popCount:      1,
			expectedEmpty: true, // стек должен остаться пустым
		},
		{
			name:          "Удаление одного значения",
			setupValues:   []string{"a", "b"},
			popCount:      1,
			expectedTop:   "a", // после удаления вершина должна быть "a"
			expectedEmpty: false,
		},
		{
			name:          "Удаление нескольких значений",
			setupValues:   []string{"a", "b", "c"},
			popCount:      2,
			expectedTop:   "a", // после двух удалений вершина должна быть "a"
			expectedEmpty: false,
		},
	}

	// проходим по всем тестовым случаям
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			stack := NewStack() // создаем новый стек для каждого теста
			for _, v := range tt.setupValues {
				stack.Push(v) // добавляем значения в стек
			}

			// выполняем удаление элементов
			for i := 0; i < tt.popCount; i++ {
				stack.Pop()
			}

			// проверяем состояние стека
			if tt.expectedEmpty {
				if stack.GetTop() != nil {
					t.Error("Ожидался пустой стек, но получен непустой")
				}
			} else {
				if stack.GetTop() == nil {
					t.Error("Ожидался непустой стек, но получен пустой")
				} else if stack.GetTop().data != tt.expectedTop {
					t.Errorf("Ожидалось значение %s на вершине, но получено %s", tt.expectedTop, stack.GetTop().data)
				}
			}
		})
	}
}

// testDisplay тестирует функцию отображения содержимого стека
func TestDisplay(t *testing.T) {
	stack := NewStack()

	// тестируем пустой стек
	stack.Display() // должно вывести "Стек пуст!"

	// тестируем стек с элементами
	values := []string{"a", "b", "c"}
	for _, v := range values {
		stack.Push(v) // добавляем значения в стек
	}
	stack.Display() // должно вывести "c b a"
}

// benchmarkPush тестирует производительность операции Push
func BenchmarkPush(b *testing.B) {
	stack := NewStack() // создаем новый стек
	b.ResetTimer()      // сбрасываем таймер перед началом теста
	for i := 0; i < b.N; i++ {
		stack.Push("test") // добавляем элемент в стек
	}
}

// benchmarkPop тестирует производительность операции Pop
func BenchmarkPop(b *testing.B) {
	stack := NewStack()
	// подготовка: добавляем 1000 элементов в стек
	for i := 0; i < 1000; i++ {
		stack.Push("test")
	}

	b.ResetTimer() // сбрасываем таймер перед началом теста
	for i := 0; i < b.N && stack.GetTop() != nil; i++ {
		stack.Pop() // удаляем элемент из стека
	}
}

// benchmarkPushPop тестирует производительность чередующихся операций Push и Pop
func BenchmarkPushPop(b *testing.B) {
	stack := NewStack() // создаем новый стек
	b.ResetTimer()      // сбрасываем таймер перед началом теста
	for i := 0; i < b.N; i++ {
		stack.Push("test") // добавляем элемент в стек
		if stack.GetTop() != nil {
			stack.Pop() // удаляем элемент из стека
		}
	}
}
