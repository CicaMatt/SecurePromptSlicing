import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClientRequest(clientSocket);
        }
    }

    private static void handleClientRequest(Socket clientSocket) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStreamWriter writer = new OutputStreamWriter(clientSocket.getOutputStream());

        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while (!(line = reader.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        String request = requestBuilder.toString();
        String[] lines = request.split("\\r?\\n");
        for (String l : lines) {
            if (l.startsWith("username=")) {
                String username = l.substring(9);
                writer.write("HTTP/1.1 200 OK\r\n");
                writer.write("Content-Type: text/plain\r\n");
                writer.write("\r\n");
                writer.write("Hello " + username + "\r\n");
                break;
            }
        }

        writer.flush();
        clientSocket.close();
    }
}