import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBody = new StringBuilder();
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            // Reading headers
        }
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        String username = requestBody.toString().trim();

        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "\r\n" +
                              "Hello " + username;

        response.write(httpResponse.getBytes());
        response.flush();
    }

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            try (Socket clientSocket = serverSocket.accept()) {
                InputStream request = clientSocket.getInputStream();
                OutputStream response = clientSocket.getOutputStream();
                http_hello_page(request, response);
            } catch (IOException e) {
                System.err.println("Error handling client: " + e.getMessage());
            }
        }
    }
}