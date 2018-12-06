package main

import "fmt"

func main() {
	fmt.Println("Hello world!")

	masks := [8]uint8{}
	mask := uint8(0)
	for i := uint8(0); i < 8; i++ {
		mask = mask | 1<<(7-i)
		masks[i] = mask
	}

	fmt.Println("Positions: %v\n", masks)
}
