import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening for connection on port 8080...");

        while (true) {
            try (Socket clientSocket = serverSocket.accept();
                 BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                 OutputStream out = clientSocket.getOutputStream()) {

                String requestLine = in.readLine();
                if (requestLine != null && requestLine.startsWith("GET /?username=")) {
                    String username = requestLine.split("=")[1];
                    String response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
                    out.write(response.getBytes());
                }
            } catch (IOException e) {
                System.err.println("Error handling client request: " + e.getMessage());
            }
        }
    }
}