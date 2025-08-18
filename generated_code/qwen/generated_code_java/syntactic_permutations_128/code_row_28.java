import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
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
        BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStreamWriter writer = new OutputStreamWriter(clientSocket.getOutputStream());

        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while (!(line = reader.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        String[] requestLines = requestBuilder.toString().split("\r\n");
        String firstLine = requestLines[0];
        String[] parts = firstLine.split(" ");
        if (parts.length < 2) {
            writer.write("HTTP/1.1 400 Bad Request\r\n\r\n");
            writer.flush();
            clientSocket.close();
            return;
        }

        String path = parts[1];
        if (!path.startsWith("/?username=")) {
            writer.write("HTTP/1.1 400 Bad Request\r\n\r\n");
            writer.flush();
            clientSocket.close();
            return;
        }

        String username = path.substring(12);
        String response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello " + username;

        writer.write(response);
        writer.flush();
        clientSocket.close();
    }
}