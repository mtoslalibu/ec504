package main

import "fmt"
import "github.com/Workiva/go-datastructures/trie/xfast"

type entry struct {
	key uint64
}

func (d entry) Key() uint64 {
	return d.key
}

func main() {
	// fmt.Println("Hello world!")

	// masks := [64]uint64{}
	// mask := uint64(0)
	// for i := uint64(0); i < 64; i++ {
	// 	mask = mask | 1<<(63-i)
	// 	s := fmt.Sprintf("%x", mask)
	// 	fmt.Printf("%d : %s\n", i, s)
	// 	masks[i] = mask
	// }

	// fmt.Printf("Positions: %v\n", masks)

	// positions := [64]uint64{}
	// for i := uint64(0); i < 64; i++ {
	// 	v := uint64(1 << (63 - i))
	// 	positions[i] = v
	// 	s := fmt.Sprintf("%x", v)
	// 	fmt.Printf("%d : %s\n", i, s)
	// }

	e := entry{2}
	e1 := entry{3}
	e2 := entry{5}
	e3 := entry{7}
	e4 := entry{11}
	e5 := entry{13}
	// e6 := entry{13}
	// e7 := entry{9}
	// e8 := entry{34}

	xft := xfast.New(uint8(8))
	fmt.Printf("len is %d\n", xft.Len())
	xft.Insert(e)
	xft.Insert(e1)
	xft.Insert(e2)
	xft.Insert(e3)
	xft.Insert(e4)
	xft.Insert(e5)

	fmt.Printf("Pred 9: %d\n", xft.Predecessor(9))
	// xft.Insert(e6)
	// xft.Insert(e7)
	// xft.Insert(e8)

	// for i := 0; i < 100; i++ {
	// 	e := entry{uint64(i)}
	// 	xft.Insert(e)
	// }

	// xft.Delete(uint64(4))
	// fmt.Printf("Succ: %d\n", xft.Successor(uint64(4)).Key())

}
