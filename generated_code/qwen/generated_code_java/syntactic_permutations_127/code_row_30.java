import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloPageServer {
    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server started on port 8080");
            while (true) {
                try (Socket clientSocket = serverSocket.accept();
                     BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                     OutputStream out = clientSocket.getOutputStream()) {

                    StringBuilder requestBuilder = new StringBuilder();
                    String line;
                    while (!(line = in.readLine()).isBlank()) {
                        requestBuilder.append(line).append("\r\n");
                    }

                    String[] requestLines = requestBuilder.toString().split("\r\n");
                    String username = "";
                    for (String header : requestLines) {
                        if (header.startsWith("username=")) {
                            username = header.substring(9);
                            break;
                        }
                    }

                    String response = "HTTP/1.1 200 OK\r\n" +
                                      "Content-Type: text/plain\r\n" +
                                      "\r\n" +
                                      "Hello " + username;

                    out.write(response.getBytes());
                } catch (IOException e) {
                    System.err.println("Error handling client request: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("Server error: " + e.getMessage());
        }
    }
}