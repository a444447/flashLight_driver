package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"time"
)

func main() {
	// 定义服务器地址和端口
	serverAddr := "192.168.31.115:4789"

	// 连接到服务器
	conn, err := net.Dial("tcp", serverAddr)
	deadline := time.Now().Add(10 * time.Second)
	conn.SetDeadline(deadline)
	if err != nil {
		fmt.Println("Error connecting:", err)
		os.Exit(1)
	}
	defer conn.Close()

	// 发送消息到服务器
	fmt.Fprintf(conn, "20.0")

	// 接收服务器的响应
	message, err := bufio.NewReader(conn).ReadString('\n')
	if err != nil {
		fmt.Println("Error reading:", err)
		os.Exit(1)
	}
	fmt.Print("Server response: " + message)
}
