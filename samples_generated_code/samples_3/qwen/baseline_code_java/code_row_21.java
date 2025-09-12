import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET /hello?username=")) {
            String username = requestLine.split("=")[1];
            String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;

            out.write(responseMessage.getBytes());
        }

        in.close();
        out.close();
        clientSocket.close();
    }
}