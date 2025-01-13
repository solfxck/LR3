package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func loadStackFromFile(stack *Stack, filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var values []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		values = append(values, scanner.Text())
	}

	for i := len(values) - 1; i >= 0; i-- {
		stack.Push(values[i])
	}

	return scanner.Err()
}

func saveStackToFile(stack *Stack, filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	current := stack.GetTop()
	for current != nil {
		_, err := writer.WriteString(current.data + "\n")
		if err != nil {
			return err
		}
		current = current.next
	}

	return writer.Flush()
}

func main() {
	stack := NewStack()
	reader := bufio.NewReader(os.Stdin)

	for {
		command, _ := reader.ReadString('\n')
		command = strings.TrimSpace(command)
		parts := strings.Fields(command)

		if len(parts) == 0 {
			continue
		}

		switch parts[0] {
		case "SPUSH":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать значение")
				continue
			}
			stack.Push(parts[1])
			fmt.Println("Элемент добавлен в стек")

		case "SPOP":
			stack.Pop()

		case "SPRINT":
			stack.Display()

		case "SLOAD":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать имя файла")
				continue
			}
			err := loadStackFromFile(stack, parts[1])
			if err != nil {
				fmt.Printf("Ошибка при загрузке файла: %v\n", err)
			} else {
				fmt.Println("Данные успешно загружены из файла")
			}

		case "SSAVE":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать имя файла")
				continue
			}
			err := saveStackToFile(stack, parts[1])
			if err != nil {
				fmt.Printf("Ошибка при сохранении файла: %v\n", err)
			} else {
				fmt.Println("Данные успешно сохранены в файл")
			}

		case "EXIT":
			return

		default:
			fmt.Println("Неизвестная команда")
		}
	}
}
