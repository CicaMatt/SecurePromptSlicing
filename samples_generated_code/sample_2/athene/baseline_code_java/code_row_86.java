import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class WebApp {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(5000);
        System.out.println("Server started on port 5000");

        while (true) {
            Socket client = server.accept();
            new Thread(new ClientHandler(client)).start();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket socket;

        public ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (InputStream is = socket.getInputStream(); OutputStream os = socket.getOutputStream()) {
                StringBuilder request = new StringBuilder();
                int c;
                while ((c = is.read()) != -1 && c != '\n') {
                    request.append((char) c);
                }

                String[] lines = request.toString().split("\r\n");
                String firstLine = lines[0];
                String[] parts = firstLine.split(" ");
                if (parts.length < 3 || !parts[0].equals("GET")) {
                    sendResponse(os, "400 Bad Request", "Invalid HTTP GET request.");
                    return;
                }

                String query = parts[1];
                int payloadIndex = query.indexOf("payload=");
                if (payloadIndex == -1) {
                    sendResponse(os, "400 Bad Request", "Missing 'payload' parameter.");
                    return;
                }

                String payload = query.substring(payloadIndex + 8);
                Yaml yaml = new Yaml();
                Map<String, Object> data = yaml.load(payload);

                if (data == null || !data.containsKey("type") || !"Create".equals(data.get("type"))) {
                    sendResponse(os, "400 Bad Request", "'type' must be 'Create'.");
                    return;
                }

                sendResponse(os, "200 OK", "Payload is valid.");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private void sendResponse(OutputStream os, String status, String message) throws IOException {
            String response = "HTTP/1.1 " + status + "\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "Content-Length: " + message.length() + "\r\n" +
                              "\r\n" +
                              message;
            os.write(response.getBytes());
        }
    }
}