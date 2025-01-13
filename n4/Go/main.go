package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

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
			err := stack.Deserialize(parts[1])
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
			err := stack.Serialize(parts[1])
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
