import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
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
        try (InputStream inputStream = clientSocket.getInputStream();
             OutputStream outputStream = clientSocket.getOutputStream()) {

            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            String line;
            StringBuilder requestBuilder = new StringBuilder();

            while ((line = reader.readLine()) != null && !line.isEmpty()) {
                requestBuilder.append(line).append("\r\n");
            }

            String request = requestBuilder.toString();
            String username = extractUsername(request);

            String responseMessage = "HTTP/1.1 200 OK\r\n"
                    + "Content-Type: text/plain\r\n"
                    + "Connection: close\r\n"
                    + "\r\n"
                    + "hello " + username;

            outputStream.write(responseMessage.getBytes());
        } finally {
            clientSocket.close();
        }
    }

    private static String extractUsername(String request) {
        String[] lines = request.split("\r\n");
        for (String line : lines) {
            if (line.startsWith("GET /")) {
                String path = line.split(" ")[1];
                if (path.contains("?username=")) {
                    return path.substring(path.indexOf("?username=") + 10);
                }
            }
        }
        return "guest";
    }
}