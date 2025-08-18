import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void http_hello_page(InputStream requestStream, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
        String line;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("GET /?username=")) {
                String[] parts = line.split("\\?");
                for (String part : parts) {
                    if (part.startsWith("username=")) {
                        String username = part.substring("username=".length());
                        sendResponse(responseStream, "Hello " + username);
                        return;
                    }
                }
            }
        }

        sendResponse(responseStream, "Hello Guest");
    }

    private static void sendResponse(OutputStream responseStream, String message) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/plain\r\n" +
                          "Content-Length: " + message.length() + "\r\n" +
                          "Connection: close\r\n\r\n" +
                          message;
        responseStream.write(response.getBytes());
        responseStream.flush();
    }

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is running on port 8080...");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            InputStream requestStream = clientSocket.getInputStream();
            OutputStream responseStream = clientSocket.getOutputStream();

            http_hello_page(requestStream, responseStream);

            clientSocket.close();
        }
    }
}