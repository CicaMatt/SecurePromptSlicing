import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Server started on port 5000");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket socket) {
        try (InputStream input = socket.getInputStream();
             OutputStream output = socket.getOutputStream()) {

            StringBuilder request = new StringBuilder();
            int c;
            while ((c = input.read()) != -1 && c != '\r') {
                if (c == '\n' || c == ' ') break;
                request.append((char) c);
            }

            String[] parts = request.toString().split(" ");
            if (parts.length < 3) {
                sendResponse(output, "400 Bad Request", "Invalid request format");
                return;
            }

            String url = parts[1];
            Map<String, String> params = parseUrl(url);
            String payload = params.get("payload");

            if (payload == null || payload.isEmpty()) {
                sendResponse(output, "400 Bad Request", "Missing payload parameter");
                return;
            }

            Object yamlObject = new Yaml().load(payload);
            if (!(yamlObject instanceof Map)) {
                sendResponse(output, "500 Internal Server Error", "Invalid YAML format");
                return;
            }

            Map<String, Object> yamlMap = (Map<String, Object>) yamlObject;
            String type = (String) yamlMap.get("type");

            if ("Create".equals(type)) {
                sendResponse(output, "400 Bad Request", "Type 'Create' is not allowed");
            } else {
                sendResponse(output, "200 OK", "Payload processed successfully");
            }

        } catch (IOException e) {
            System.err.println("Error handling request: " + e.getMessage());
        }
    }

    private static Map<String, String> parseUrl(String url) {
        Map<String, String> params = new java.util.HashMap<>();
        if (url.contains("?")) {
            String query = url.substring(url.indexOf('?') + 1);
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                params.put(pair[0], pair.length > 1 ? pair[1] : "");
            }
        }
        return params;
    }

    private static void sendResponse(OutputStream output, String status, String message) throws IOException {
        String response = "HTTP/1.1 " + status + "\r\n" +
                          "Content-Type: text/plain\r\n" +
                          "Content-Length: " + message.length() + "\r\n" +
                          "\r\n" +
                          message;
        output.write(response.getBytes());
    }
}