import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening for connections on port 8080...");

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
            String response = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "\r\n" +
                              "Hello " + username;
            out.write(response.getBytes());
        }

        out.close();
        in.close();
        clientSocket.close();
    }
}