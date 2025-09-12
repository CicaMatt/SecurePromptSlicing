import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import org.yaml.snakeyaml.Yaml;

public class Server {
    public static void main(String[] args) throws IOException {
        try (ServerSocket server = new ServerSocket(5000)) {
            System.out.println("Listening on port 5000");
            while (true) {
                Socket client = server.accept();
                handleRequest(client);
            }
        }
    }

    private static void handleRequest(Socket client) throws IOException {
        try (Scanner in = new Scanner(client.getInputStream());
             OutputStream out = client.getOutputStream()) {

            String request = in.useDelimiter("\\r?\\n").nextLine();
            String[] parts = request.split(" ");
            if (!"GET".equals(parts[0])) {
                sendResponse(out, "Only GET requests are supported", 400);
                return;
            }

            String query = parts[1].substring(2); // Skip the "?"
            String payload = getParameter(query, "payload");
            if (payload == null) {
                sendResponse(out, "Missing 'payload' parameter", 400);
                return;
            }

            Object yamlObject = new Yaml().load(payload);
            if (!(yamlObject instanceof java.util.Map)) {
                sendResponse(out, "Invalid YAML format", 400);
                return;
            }

            java.util.Map<String, Object> map = (java.util.Map<String, Object>) yamlObject;
            String type = (String) map.get("type");
            if ("Create".equals(type)) {
                sendResponse(out, "Type 'Create' is not allowed", 400);
                return;
            }

            sendResponse(out, "Request processed successfully", 200);
        } finally {
            client.close();
        }
    }

    private static String getParameter(String query, String key) {
        for (String param : query.split("&")) {
            String[] pair = param.split("=");
            if (pair.length == 2 && key.equals(pair[0])) {
                return pair[1];
            }
        }
        return null;
    }

    private static void sendResponse(OutputStream out, String message, int statusCode) throws IOException {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(statusCode).append(" OK\r\n");
        response.append("Content-Type: text/plain\r\n");
        response.append("Content-Length: ").append(message.length()).append("\r\n");
        response.append("Connection: close\r\n");
        response.append("\r\n");
        response.append(message);
        out.write(response.toString().getBytes());
        out.flush();
    }
}