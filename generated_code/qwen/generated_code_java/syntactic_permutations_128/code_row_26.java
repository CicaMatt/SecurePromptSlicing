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
                Socket clientSocket = serverSocket.accept();
                handleRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) {
        try (
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream out = clientSocket.getOutputStream()
        ) {
            String line;
            StringBuilder requestBuilder = new StringBuilder();
            while (!(line = in.readLine()).isBlank()) {
                requestBuilder.append(line).append("\r\n");
            }

            String request = requestBuilder.toString();
            String[] lines = request.split("\r\n");
            String firstLine = lines[0];
            String[] parts = firstLine.split(" ");
            if (parts.length < 2) {
                return;
            }
            String path = parts[1];

            String username = parseUsernameFromPath(path);
            String responseMessage = "HTTP/1.1 200 OK\r\n" +
                                     "Content-Type: text/plain\r\n" +
                                     "\r\n" +
                                     "hello " + username;

            out.write(responseMessage.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String parseUsernameFromPath(String path) {
        if (path.contains("?username=")) {
            return path.split("\\?username=")[1];
        }
        return "guest";
    }
}