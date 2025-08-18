import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             OutputStream out = clientSocket.getOutputStream()) {

            String line;
            StringBuilder requestBuilder = new StringBuilder();
            while (!(line = in.readLine()).isBlank()) {
                requestBuilder.append(line).append("\r\n");
            }

            String request = requestBuilder.toString();
            String[] lines = request.split("\\r\\n");
            String firstLine = lines[0];
            String[] parts = firstLine.split(" ");
            if (parts.length >= 2) {
                String path = parts[1];
                int queryIndex = path.indexOf('?');
                if (queryIndex != -1 && path.startsWith("/hello?username=")) {
                    String username = path.substring(queryIndex + "username=".length());
                    String responseContent = "Hello " + username;
                    sendResponse(out, responseContent);
                } else {
                    sendErrorResponse(out);
                }
            } else {
                sendErrorResponse(out);
            }
        }
    }

    private static void sendResponse(OutputStream out, String content) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/plain\r\n" +
                          "Content-Length: " + content.length() + "\r\n" +
                          "Connection: close\r\n" +
                          "\r\n" +
                          content;
        out.write(response.getBytes());
    }

    private static void sendErrorResponse(OutputStream out) throws IOException {
        String response = "HTTP/1.1 400 Bad Request\r\n" +
                          "Content-Type: text/plain\r\n" +
                          "Connection: close\r\n" +
                          "\r\n" +
                          "Invalid request";
        out.write(response.getBytes());
    }
}