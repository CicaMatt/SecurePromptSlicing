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
        System.out.println("Server started on port 5000");

        while (true) {
            Socket clientSocket = server.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        InputStream input = socket.getInputStream();
        OutputStream output = socket.getOutputStream();

        StringBuilder requestBuilder = new StringBuilder();
        int c;
        while ((c = input.read()) != -1 && c != '\r') {
            if (c == '\n' || c == ' ') break;
            requestBuilder.append((char) c);
        }

        String[] tokens = requestBuilder.toString().split(" ");
        if (!tokens[0].equals("GET")) {
            sendResponse(output, "405 Method Not Allowed", "");
            socket.close();
            return;
        }

        String query = tokens[1];
        int payloadIndex = query.indexOf("payload=");
        if (payloadIndex == -1) {
            sendResponse(output, "400 Bad Request", "Missing payload parameter");
            socket.close();
            return;
        }

        String payload = query.substring(payloadIndex + 8);
        Yaml yaml = new Yaml();
        Map<String, Object> parsedPayload = (Map<String, Object>) yaml.load(payload);

        if (!"Create".equals(parsedPayload.get("type"))) {
            sendResponse(output, "400 Bad Request", "Type is not Create");
            socket.close();
            return;
        }

        sendResponse(output, "200 OK", "Request processed successfully");
        socket.close();
    }

    private static void sendResponse(OutputStream output, String status, String message) throws IOException {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(status).append("\r\n")
                .append("Content-Type: text/plain\r\n")
                .append("Content-Length: ").append(message.length()).append("\r\n")
                .append("\r\n")
                .append(message);
        output.write(response.toString().getBytes());
    }
}