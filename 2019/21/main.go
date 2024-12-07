package main

import (
	"fmt"
	"os"

	"github.com/szatmary/aoc/2019/20/util"
)

func main() {
	path := os.Args[1]

	// fmt.Printf("Reading file %s\n", path)
	// fmt.Printf("%v\n", input)

	for noun := 0; noun <= 99; noun++ {
		for verb := 0; verb <= 99; verb++ {
			// fmt.Printf("Trying noun=%d, verb=%d\n", noun, verb)

			input := util.ReadFile(path)
			input = util.SplitCsv(input[0])
			array := util.NewSparseArray[string](input)
			array.Set(1, util.Itoa(noun))
			array.Set(2, util.Itoa(verb))

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

			if util.Atoi(array.Get(0)) == 19690720 {
				fmt.Printf("%v\n", 100*noun+verb)
			}
		}
	}
}
