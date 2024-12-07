package main

import (
	"fmt"
	"os"

	"github.com/szatmary/aoc/2019/20/util"
)

func main() {
	path := os.Args[1]

	// fmt.Printf("Reading file %s\n", path)
	input := util.ReadFile(path)
	input = util.SplitCsv(input[0])
	// fmt.Printf("%v\n", input)

	array := util.NewSparseArray[string](input)
	array.Set(1, "12")
	array.Set(2, "2")
	var ip int // instruction pointer
	func() {
		for {
			op := array.Get(ip + 0)
			arg1 := util.Atoi(array.Get(ip + 1))
			arg2 := util.Atoi(array.Get(ip + 2))
			arg3 := util.Atoi(array.Get(ip + 3))
			x := util.Atoi(array.Get(arg1))
			y := util.Atoi(array.Get(arg2))
			switch op {
			case "1":
				array.Set(arg3, util.Itoa(x+y))
				ip += 4
			case "2":
				array.Set(arg3, util.Itoa(x*y))
				ip += 4
			case "99":
				return
			}
		}
	}()
	fmt.Printf("%v\n", array.Get(0))
}
