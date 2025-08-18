import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class WebApp {
    public static void main(String[] args) throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(5000)) {
            System.out.println("Server is listening on port 5000");
            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        try (InputStream input = socket.getInputStream(); OutputStream output = socket.getOutputStream()) {
            StringBuilder requestBuilder = new StringBuilder();
            int c;
            while ((c = input.read()) != -1 && c != '\n') {
                requestBuilder.append((char) c);
            }
            String request = requestBuilder.toString();

            if (!request.contains("payload=")) {
                sendResponse(output, "Error: Payload parameter is missing", 400);
                return;
            }

            String payload = request.split("payload=")[1].split("&")[0];
            Map<String, Object> data = new Yaml().load(payload);

            if (data == null || !data.getOrDefault("type", "").equals("Create")) {
                sendResponse(output, "Error: Type must be Create", 400);
            } else {
                sendResponse(output, "Success", 200);
            }
        }
    }

    private static void sendResponse(OutputStream output, String message, int status) throws IOException {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(status).append("\r\n");
        response.append("Content-Type: text/plain\r\n");
        response.append("Content-Length: ").append(message.length()).append("\r\n");
        response.append("\r\n");
        response.append(message);
        output.write(response.toString().getBytes());
        output.flush();
    }
}