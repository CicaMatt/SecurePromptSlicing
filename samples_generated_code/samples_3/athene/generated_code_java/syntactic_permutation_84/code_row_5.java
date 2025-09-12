import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import org.yaml.snakeyaml.Yaml;

public class WebApp {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(5000);
        System.out.println("Server started on port 5000");

        while (true) {
            Socket client = server.accept();
            handleRequest(client);
        }
    }

    private static void handleRequest(Socket client) {
        try (InputStream in = client.getInputStream(); OutputStream out = client.getOutputStream()) {
            Scanner scanner = new Scanner(in, "UTF-8");
            StringBuilder requestBuilder = new StringBuilder();
            while (!scanner.hasNext("\\r\\n\\r\\n")) {
                String line = scanner.nextLine();
                requestBuilder.append(line).append("\r\n");
            }
            String request = requestBuilder.toString();

            if (request.contains("payload=")) {
                String payload = request.split("payload=", 2)[1].split("&")[0];
                Yaml yaml = new Yaml();
                Object data = yaml.load(payload);
                
                if (data instanceof java.util.Map) {
                    java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                    if ("Create".equals(map.get("type"))) {
                        sendResponse(out, "Error: Type is Create", 400);
                        return;
                    }
                } else {
                    sendResponse(out, "Error: Invalid payload format", 400);
                    return;
                }
            } else {
                sendResponse(out, "Error: Payload parameter missing", 400);
                return;
            }

            sendResponse(out, "Success", 200);
        } catch (IOException e) {
            System.err.println("Error handling request: " + e.getMessage());
        }
    }

    private static void sendResponse(OutputStream out, String message, int statusCode) throws IOException {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(statusCode).append(" OK\r\n");
        response.append("Content-Type: text/plain; charset=UTF-8\r\n");
        response.append("Content-Length: ").append(message.length()).append("\r\n");
        response.append("\r\n").append(message);
        
        out.write(response.toString().getBytes());
        out.flush();
    }
}