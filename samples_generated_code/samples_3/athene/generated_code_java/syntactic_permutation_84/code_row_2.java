import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) throws IOException {
        try (ServerSocket server = new ServerSocket(5000)) {
            System.out.println("Listening on port 5000");
            while (true) {
                Socket socket = server.accept();
                new Thread(new Handler(socket)).start();
            }
        }
    }

    static class Handler implements Runnable {
        private final Socket socket;

        public Handler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                 PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

                String line;
                StringBuilder requestBuilder = new StringBuilder();
                while (!(line = in.readLine()).isEmpty()) {
                    requestBuilder.append(line).append("\n");
                }
                String request = requestBuilder.toString();

                String[] parts = request.split("&");
                Map<String, String> params = parseQuery(parts);

                if (!params.containsKey("payload")) {
                    out.println("HTTP/1.1 400 Bad Request");
                    out.println("Content-Type: text/plain");
                    out.println();
                    out.println("Error: Missing payload parameter.");
                    return;
                }

                String payload = params.get("payload");
                Map<String, Object> yamlMap = new Yaml().load(payload);
                if (yamlMap == null || !"Create".equals(yamlMap.get("type"))) {
                    out.println("HTTP/1.1 400 Bad Request");
                    out.println("Content-Type: text/plain");
                    out.println();
                    out.println("Error: Invalid payload type.");
                    return;
                }

                out.println("HTTP/1.1 200 OK");
                out.println("Content-Type: text/plain");
                out.println();
                out.println("Payload processed successfully.");

            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private Map<String, String> parseQuery(String[] parts) {
            Map<String, String> params = new java.util.HashMap<>();
            for (String part : parts) {
                String[] keyValue = part.split("=");
                if (keyValue.length == 2) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }
            return params;
        }
    }
}