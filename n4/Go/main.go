package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	queue := NewQueue()
	reader := bufio.NewReader(os.Stdin)

	for {
		command, _ := reader.ReadString('\n')
		command = strings.TrimSpace(command)
		parts := strings.Fields(command)

		if len(parts) == 0 {
			continue
		}

		switch parts[0] {
		case "QPUSH":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать значение")
				continue
			}
			queue.Push(parts[1])
			fmt.Println("Элемент добавлен в очередь")

		case "QPOP":
			queue.Pop()

		case "QPRINT":
			queue.Display()

		case "QLOAD":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать имя файла")
				continue
			}
			err := queue.Deserialize(parts[1])
			if err != nil {
				fmt.Printf("Ошибка при загрузке файла: %v\n", err)
			} else {
				fmt.Println("Данные успешно загружены из файла")
			}

		case "QSAVE":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать имя файла")
				continue
			}
			err := queue.Serialize(parts[1])
			if err != nil {
				fmt.Printf("Ошибка при сохранении файла: %v\n", err)
			} else {
				fmt.Println("Данные успешно сохранены в файл")
			}

		case "QLOADTEXT":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать имя файла")
				continue
			}
			err := queue.DeserializeText(parts[1])
			if err != nil {
				fmt.Printf("Ошибка при загрузке текстового файла: %v\n", err)
			} else {
				fmt.Println("Данные успешно загружены из текстового файла")
			}

		case "QSAVETEXT":
			if len(parts) < 2 {
				fmt.Println("Ошибка: необходимо указать имя файла")
				continue
			}
			err := queue.SerializeText(parts[1])
			if err != nil {
				fmt.Printf("Ошибка при сохранении в текстовый файл: %v\n", err)
			} else {
				fmt.Println("Данные успешно сохранены в текстовый файл")
			}

		case "EXIT":
			return

		default:
			fmt.Println("Неизвестная команда")
		}
	}
}
