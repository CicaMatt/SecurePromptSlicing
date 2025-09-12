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

        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while ((line = in.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }

        String request = requestBuilder.toString();
        String[] lines = request.split("\r\n");
        if (lines.length > 0) {
            String firstLine = lines[0];
            String[] parts = firstLine.split(" ");
            if (parts.length == 3 && "GET".equals(parts[0])) {
                String query = parts[1];
                if (query.startsWith("/?username=")) {
                    String username = query.substring("/?username=".length());
                    sendResponse(out, username);
                }
            }
        }

        clientSocket.close();
    }

    private static void sendResponse(OutputStream out, String username) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/html\r\n" +
                          "\r\n" +
                          "<html><body><h1>Hello " + username + "</h1></body></html>";
        out.write(response.getBytes());
        out.flush();
    }
}