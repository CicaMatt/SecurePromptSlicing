import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(5000);
        System.out.println("Server started on port 5000");

        while (true) {
            Socket client = server.accept();
            handleRequest(client);
        }
    }

    private static void handleRequest(Socket client) {
        try (InputStream input = client.getInputStream(); OutputStream output = client.getOutputStream()) {
            StringBuilder request = new StringBuilder();
            int c;
            while ((c = input.read()) != -1 && c != '\n') {
                request.append((char) c);
            }

            if (!request.toString().contains("payload=")) {
                sendResponse(output, "Error: Missing payload parameter", 400);
                return;
            }

            String payload = request.toString().split("payload=")[1].split("&")[0];
            Object parsedPayload = new Yaml().load(payload);

            if (parsedPayload instanceof java.util.Map) {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> map = (java.util.Map<String, Object>) parsedPayload;
                if ("Create".equals(map.get("type"))) {
                    sendResponse(output, "Error: Type Create is not allowed", 400);
                    return;
                }
            }

            sendResponse(output, "OK", 200);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void sendResponse(OutputStream output, String message, int status) throws IOException {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(status).append("\r\n");
        response.append("Content-Type: text/plain\r\n");
        response.append("Content-Length: ").append(message.length()).append("\r\n");
        response.append("\r\n").append(message);
        output.write(response.toString().getBytes());
        output.flush();
    }
}