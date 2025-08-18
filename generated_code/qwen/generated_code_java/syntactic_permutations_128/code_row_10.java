import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server is listening on port 8080");
            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        OutputStream outputStream = socket.getOutputStream();

        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while (!(line = reader.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        String[] requestLines = requestBuilder.toString().split("\\r\\n");
        for (String headerLine : requestLines) {
            if (headerLine.startsWith("GET /")) {
                String[] parts = headerLine.split("\\?");
                if (parts.length > 1) {
                    String query = parts[1];
                    if (query.startsWith("username=")) {
                        String username = query.substring(9);
                        sendResponse(outputStream, "hello " + username);
                    }
                }
            }
        }

        outputStream.close();
        reader.close();
        socket.close();
    }

    private static void sendResponse(OutputStream outputStream, String message) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/plain\r\n" +
                          "Content-Length: " + message.length() + "\r\n" +
                          "\r\n" +
                          message;
        outputStream.write(response.getBytes());
    }
}