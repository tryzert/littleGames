package main

import (
	"github.com/mattn/go-gtk/gtk"
	"github.com/mattn/go-gtk/glib"
	"github.com/mattn/go-gtk/gdk"
	"unsafe"
	"os"
	// "fmt"
	"math/rand"
	"time"
	"errors"
	"strconv"
	"strings"
	"io/ioutil"
)


var (
	board [4][4]int
	bestScore int
	bestScoreLabel *gtk.Label
	score int
	scoreLabel *gtk.Label
)


// func printBoard() {
// 	for _, i := range board {
// 		fmt.Println(i)
// 	}
// }


func initBoard() {
	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			board[i][j] = 0
		}
	}
	randomNum()
}


func randomNum() error {
	rand.Seed(time.Now().UnixNano())
	var blankSpace [][2]int
	for x := 0; x < 4; x++ {
		for y := 0; y < 4; y++ {
			if board[x][y] == 0 {
				blankSpace = append(blankSpace, [2]int{x, y})
			}
		}
	}
	if len(blankSpace) == 0 {
		return errors.New("no space")
	}
	pos := rand.Intn(len(blankSpace))
	n := 4
	if psb := rand.Intn(100); psb < 90 {
		n = 2
	}
	board[blankSpace[pos][0]][blankSpace[pos][1]] = n
	return nil
}


func keyUpPressed() {
	for c := 0; c < 4; c++ {
		for i := 0; i < 3; i++ {
			for j := i; j < 3; j++ {
				if board[j][c] == 0 {
					board[j][c], board[j + 1][c] = board[j + 1][c], board[j][c]
				}
			}
		}
		if board[0][c] == board[1][c] {
			board[0][c] *= 2
			board[1][c] = 0
			score += board[0][c]
			if board[2][c] == board[3][c] {
				board[2][c] *= 2
				board[3][c] = 0
				score += board[2][c]
			}
		} else if board[1][c] == board[2][c] {
			board[1][c] *= 2
			board[2][c] = 0
			score += board[1][c]
		} else if board[2][c] == board[3][c] {
			board[2][c] *= 2
			board[3][c] = 0
			score += board[2][c]
		}
		for i := 0; i < 3; i++ {
			for j := i; j < 3; j++ {
				if board[j][c] == 0 {
					board[j][c], board[j + 1][c] = board[j + 1][c], board[j][c]
				}
			}
		}
	}
}


func keyDownPressed() {
	for c := 0; c < 4; c++ {
		for i := 3; i > 0; i-- {
			for j := i; j > 0; j-- {
				if board[j][c] == 0 {
					board[j][c], board[j - 1][c] = board[j - 1][c], board[j][c]
				}
			}
		}
		if board[3][c] == board[2][c] {
			board[3][c] *= 2
			board[2][c] = 0
			score += board[3][c]
			if board[1][c] == board[0][c] {
				board[1][c] *= 2
				board[0][c] = 0
				score += board[1][c]
			}
		} else if board[2][c] == board[1][c] {
			board[2][c] *= 2
			board[1][c] = 0
			score += board[2][c]
		} else if board[1][c] == board[0][c] {
			board[1][c] *= 2
			board[0][c] = 0
			score += board[1][c]
		}
		for i := 3; i > 0; i-- {
			for j := i; j > 0; j-- {
				if board[j][c] == 0 {
					board[j][c], board[j - 1][c] = board[j - 1][c], board[j][c]
				}
			}
		}
	}
}


func keyLeftPressed() {
	for r := 0; r < 4; r++ {
		for i := 0; i < 3; i++ {
			for j := i; j < 3; j++ {
				if board[r][j] == 0 {
					board[r][j], board[r][j + 1] = board[r][j + 1], board[r][j]
				}
			}
		}
		if board[r][0] == board[r][1] {
			board[r][0] *= 2
			board[r][1] = 0
			score += board[r][0]
			if board[r][2] == board[r][3] {
				board[r][2] *= 2
				board[r][3] = 0
				score += board[r][2]
			}
		} else if board[r][1] == board[r][2] {
			board[r][1] *= 2
			board[r][2] = 0
			score += board[r][1]
		} else if board[r][2] == board[r][3] {
			board[r][2] *= 2
			board[r][3] = 0
			score += board[r][2]
		}
		for i := 0; i < 3; i++ {
			for j := i; j < 3; j++ {
				if board[r][j] == 0 {
					board[r][j], board[r][j + 1] = board[r][j + 1], board[r][j]
				}
			}
		}
	}
}


func keyRightPressed() {
	for r := 0; r < 4; r++ {
		for i := 3; i > 0; i-- {
			for j := i; j > 0; j-- {
				if board[r][j] == 0 {
					board[r][j], board[r][j - 1] = board[r][j - 1], board[r][j]
				}
			}
		}
		if board[r][3] == board[r][2] {
			board[r][3] *= 2
			board[r][2] = 0
			score += board[r][3]
			if board[r][1] == board[r][0] {
				board[r][1] *= 2
				board[r][0] = 0
				score += board[r][1]
			}
		} else if board[r][2] == board[r][1] {
			board[r][2] *= 2
			board[r][1] = 0
			score += board[r][2]
		} else if board[r][1] == board[r][0] {
			board[r][1] *= 2
			board[r][0] = 0
			score += board[r][1]
		}
		for i := 3; i > 0; i-- {
			for j := i; j > 0; j-- {
				if board[r][j] == 0 {
					board[r][j], board[r][j - 1] = board[r][j - 1], board[r][j]
				}
			}
		}
	}
}


var numBlocks [4][4]*gtk.Label


func initScore() {
	f, err := ioutil.ReadFile("./2048.conf")
	if err != nil {
		bestScore = 0
	}
	bestScore, err = strconv.Atoi(strings.Trim(string(f), "\n"))
	if err != nil {
		bestScore = 0
	}
}


func readScore() int {
	f, err := ioutil.ReadFile("./2048.conf")
	if err != nil {
		return 0
	}
	s, err := strconv.Atoi(strings.Trim(string(f), "\n"))
	if err != nil {
		return 0
	}
	return s
}


func saveScore() {
	ioutil.WriteFile("./2048.conf", []byte(strconv.Itoa(bestScore)), 777)
}


func setLabel(w *gtk.Window) {
	blockSideLength := 47
	topMargin := 50
	leftMargin := 3

	mainLayout := gtk.NewFixed()

	bestScoreLabel = gtk.NewLabel("最高:" + strconv.Itoa(bestScore))
	bestScoreLabel.SetSizeRequest(90, 50)
	mainLayout.Put(bestScoreLabel,0, 5)

	scoreLabel = gtk.NewLabel("得分:0")
	scoreLabel.SetSizeRequest(90, 50)
	mainLayout.Put(scoreLabel, 100, 5)
	for x := 0; x < 4; x++ {
		for y := 0; y < 4; y++ {
			block := gtk.NewLabel("")
			block.SetSizeRequest(blockSideLength, blockSideLength)
			// block.SetLineWrap(true)
			block.SetTrackVisitedLinks(true)
			numBlocks[x][y] = block
			mainLayout.Put(block, leftMargin + y * blockSideLength, topMargin + x * blockSideLength)
		}
	}
	w.Add(mainLayout)
}


func initWindow() {
	gtk.Init(&os.Args)
	window := gtk.NewWindow(gtk.WINDOW_TOPLEVEL)
	window.SetTitle("2048")
	window.SetResizable(false)
	window.Connect("destroy", gtk.MainQuit)

	setLabel(window)
	keyPressEvent(window)

	initScore()
	updateWindow()
	window.ShowAll()
	window.SetSizeRequest(200, 250)
	gtk.Main()
}


func updateWindow() {
	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			if board[i][j] > 0 {
				numBlocks[i][j].SetText(strconv.Itoa(board[i][j]))
			} else {
				numBlocks[i][j].SetText("")
			}
		}
	}
	scoreLabel.SetText("得分:" + strconv.Itoa(score))
	if score > bestScore {
		bestScore = score
	}
	bestScoreLabel.SetText("最高:" + strconv.Itoa(bestScore))
}


func checkGameOver(w *gtk.Window) {
	err := randomNum()
	flag := true
	if err != nil {
		for i := 0; i < 4; i++ {
			for j := 0; j < 3; j++ {
				if board[i][j] == board[i][j + 1] {
					flag = false
				}
				if board[j][i] == board[j + 1][i] {
					flag = false
				}
			}
		}
	}
	if err != nil && flag {
		messageBox(w)
		if bestScore > readScore() {
			saveScore()
		}
	}
}


func keyPressEvent(w *gtk.Window) {
	w.Connect("key-press-event", func(ctx *glib.CallbackContext){
		arg := ctx.Args(0)
		event := *(**gdk.EventKey)(unsafe.Pointer(&arg))
		key := event.Keyval

		if key == 65362 {
			keyUpPressed()			
		}
		if key == 65364 {
			keyDownPressed()
		}
		if key == 65361 {
			keyLeftPressed()
		}
		if key == 65363 {
			keyRightPressed()
		}
		checkGameOver(w)
		updateWindow()
	})
}


func messageBox(w *gtk.Window) {
	dialog := gtk.NewMessageDialog(
		w,
		gtk.DIALOG_MODAL,
		gtk.MESSAGE_QUESTION,
		gtk.BUTTONS_YES_NO,
		"在玩一局？")
	dialog.SetTitle("游戏结束")
	flag := dialog.Run()
	if flag == gtk.RESPONSE_YES {
		score = 0
		initBoard()
		updateWindow()
	} else if flag == gtk.RESPONSE_NO {
		os.Exit(0)
	}
	dialog.Destroy()
}


func main() {
	randomNum()
	initWindow()
}