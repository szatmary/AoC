package util

import (
	"bufio"
	"io"
	"os"
	"strconv"
	"strings"
)

func Atoi(s string) int {
	n, err := strconv.Atoi(s)
	if err != nil {
		panic(err)
	}
	return n
}

func Itoa(i int) string {
	return strconv.Itoa(i)
}

type SparseArray[T any] struct {
	Values map[int]T
	Len    int
}

func NewSparseArray[T any](in []T) *SparseArray[T] {
	s := &SparseArray[T]{
		Len:    len(in),
		Values: make(map[int]T),
	}
	for i, v := range in {
		s.Values[i] = v
	}
	return s
}

func (s *SparseArray[T]) Get(i int) T {
	if v, ok := s.Values[i]; ok {
		return v
	}
	// return the zero value of T
	var dflt T
	return dflt
}

func (s *SparseArray[T]) Set(i int, v T) {
	s.Values[i] = v
	if i >= s.Len {
		s.Len = i + 1
	}
}

func (s *SparseArray[T]) Delete(i int) {
	delete(s.Values, i)
}

func (s *SparseArray[T]) Length() int {
	return len(s.Values)
}

func (s *SparseArray[T]) ForEach(f func(int, T)) {
	for i := 0; i < s.Len; i++ {
		if v, ok := s.Values[i]; ok {
			f(i, v)
		}
	}
}

// /////////////////////////////////////////////////////////////////////////////
func SplitCsv(s string) []string {
	return strings.Split(s, ",")
}

func ReadFile(path string) []string {
	var lines []string
	if path == "" {
		path = os.Args[1]
	}
	f, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	rd := bufio.NewReader(f)
	for {
		line, err := rd.ReadString('\n')
		lines = append(lines, line)
		if err == io.EOF {
			// if line != "" {
			// 	lines = append(lines, line)
			// }
			break
		} else if err != nil {
			panic(err)
		}
	}
	return lines
}

type Input struct {
	Lines []string
}

func NewInput(path string, delim byte) *Input {
	i := &Input{}
	if path == "" {
		path = os.Args[1]
	}
	if delim == 0 {
		delim = '\n'
	}
	f, err := os.OpenFile(path, os.O_RDONLY, 0)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	rd := bufio.NewReader(f)
	for {
		line, err := rd.ReadString(delim)
		if err == io.EOF {
			break
		} else if err != nil {
			panic(err)
		}
		i.Lines = append(i.Lines, string(line))
	}
	return i
}

func (i *Input) Copy() *Input {
	c := &Input{}
	c.Lines = make([]string, len(i.Lines))
	copy(c.Lines, i.Lines)
	return c
}

func (i *Input) Height() int {
	return len(i.Lines)
}

func (i *Input) LineWidth(n int) int {
	return len(i.Lines[n])
}

func (i *Input) MaxLineWidth() int {
	max := 0
	for _, line := range i.Lines {
		if len(line) > max {
			max = len(line)
		}
	}
	return max
}

func (i *Input) Width() int {
	return i.MaxLineWidth()
}

func (i *Input) Get(x, y int) byte {
	return i.Lines[y][x]
}

func (i *Input) Set(x, y int, b byte) {
	i.Lines[y] = i.Lines[y][:x] + string(b) + i.Lines[y][x+1:]
}
