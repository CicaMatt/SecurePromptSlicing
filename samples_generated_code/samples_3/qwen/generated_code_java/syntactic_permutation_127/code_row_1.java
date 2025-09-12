import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            handleRequest(socket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine;
        StringBuilder requestBuilder = new StringBuilder();
        while (!(requestLine = in.readLine()).isBlank()) {
            requestBuilder.append(requestLine).append("\r\n");
        }

        String request = requestBuilder.toString();
        String[] lines = request.split("\\r?\\n");
        if (lines.length > 0) {
            String[] parts = lines[0].split(" ");
            if (parts.length == 3 && "GET".equals(parts[0])) {
                String path = parts[1];
                String username = extractUsername(path);
                String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                responseMessage += "<html><body><h1>Hello " + username + "</h1></body></html>";

                out.write(responseMessage.getBytes());
            }
        }

        in.close();
        out.close();
        clientSocket.close();
    }

    private static String extractUsername(String path) {
        if (path.startsWith("/?username=")) {
            return path.substring(12);
        }
        return "Guest";
    }
}