import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;

import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(5000);
        System.out.println("Server started on port 5000");

        while (true) {
            Socket client = server.accept();
            new Thread(new ClientHandler(client)).start();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket client;

        public ClientHandler(Socket client) {
            this.client = client;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()))) {
                StringBuilder request = new StringBuilder();
                String line;
                while ((line = in.readLine()) != null && !line.isEmpty()) {
                    request.append(line).append("\n");
                }

                if (request.indexOf("payload=") == -1) {
                    sendResponse("Error: Missing payload parameter", client);
                    return;
                }

                String payload = request.substring(request.indexOf("payload=") + 8);
                Map<String, Object> data = new Yaml().load(payload);

                if (!"Create".equals(data.get("type"))) {
                    sendResponse("Error: Type is not Create", client);
                } else {
                    sendResponse("Success: Payload type is Create", client);
                }

            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    client.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private void sendResponse(String message, Socket client) throws IOException {
            String response = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "Content-Length: " + message.length() + "\r\n" +
                              "\r\n" +
                              message;
            client.getOutputStream().write(response.getBytes());
        }
    }
}