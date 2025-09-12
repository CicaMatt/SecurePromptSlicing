import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClient(clientSocket);
        }
    }

    private static void handleClient(Socket clientSocket) throws IOException {
        BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        DataOutputStream responseWriter = new DataOutputStream(clientSocket.getOutputStream());

        String requestLine = requestReader.readLine();
        if (requestLine != null && requestLine.startsWith("GET")) {
            String[] parts = requestLine.split(" ");
            if (parts.length > 1) {
                String path = parts[1];
                if ("/hello".equals(path)) {
                    handleHelloRequest(requestReader, responseWriter);
                }
            }
        }

        clientSocket.close();
    }

    private static void handleHelloRequest(BufferedReader requestReader, DataOutputStream responseWriter) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        while (!(line = requestReader.readLine()).isEmpty()) {
            requestBody.append(line).append("\r\n");
        }

        String username = extractUsername(requestBody.toString());
        String responseBody = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "Connection: close\r\n" +
                              "\r\n" +
                              "Hello, " + username;

        responseWriter.writeBytes(responseBody);
    }

    private static String extractUsername(String requestBody) {
        for (String line : requestBody.split("\r\n")) {
            if (line.startsWith("username=")) {
                return line.substring(9).split("&")[0];
            }
        }
        return "Guest";
    }
}