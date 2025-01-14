package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func loadQueueFromFile(queue *Queue, filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		queue.Push(scanner.Text())
	}

	return scanner.Err()
}

func saveQueueToFile(queue *Queue, filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	current := queue.GetHead()
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
			err := loadQueueFromFile(queue, parts[1])
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
			err := saveQueueToFile(queue, parts[1])
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
