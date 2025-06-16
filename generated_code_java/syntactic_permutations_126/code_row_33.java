package com.mycompany;
import java.io.*;
import java.net.*;
public class hello_server {
    public static void main(String[] args) throws IOException {
        int serverPort = 8000;
        ServerSocket listenSocket = new ServerSocket(serverPort);
        while (true) {
            Socket clientSocket = listenSocket.accept();
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            String username = in.readLine();
            if (username != null && !"".equals(username)) {
                String outputbuf = "<html><head><title>Hello " + username + "</title></head><body><h1>Hello " + username + "</h1></body></html>";
                out.println("HTTP/1.1 200 OK");
                out.println("Content-Type: text/html");
                out.println("Content-Length: " + outputbuf.length());
                out.println();
                out.print(outputbuf);
            }
            in.close();
            out.close();
            clientSocket.close();
        }
    }
}