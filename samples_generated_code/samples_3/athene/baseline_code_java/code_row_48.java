import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(5000);
        System.out.println("Server listening on port 5000");

        while (true) {
            Socket client = server.accept();
            handleRequest(client);
        }
    }

    private static void handleRequest(Socket client) {
        try (InputStream is = client.getInputStream(); OutputStream os = client.getOutputStream()) {
            StringBuilder request = new StringBuilder();
            int c;
            while ((c = is.read()) != -1 && c != '\n') {
                request.append((char) c);
            }

            String[] lines = request.toString().split("\r\n");
            if (lines.length == 0) return;

            String[] parts = lines[0].split(" ");
            if (parts.length < 2) return;

            String query = parts[1];
            int payloadIndex = query.indexOf("payload=");
            if (payloadIndex == -1) {
                sendResponse(os, "Error: Missing payload parameter", 400);
                return;
            }

            String payload = query.substring(payloadIndex + "payload=".length());
            Map<String, Object> yamlMap = new Yaml().load(payload);

            if ("Create".equals(yamlMap.get("type"))) {
                sendResponse(os, "Error: Type 'Create' is not allowed", 400);
                return;
            }

            sendResponse(os, "Payload received successfully", 200);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void sendResponse(OutputStream os, String message, int status) throws IOException {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(status).append(" OK\r\n");
        response.append("Content-Type: text/plain\r\n");
        response.append("\r\n");
        response.append(message);
        os.write(response.toString().getBytes());
        os.flush();
    }
}