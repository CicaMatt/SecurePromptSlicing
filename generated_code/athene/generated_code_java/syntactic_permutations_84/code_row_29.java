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
            handleRequest(client);
        }
    }

    private static void handleRequest(Socket client) throws IOException {
        InputStream in = client.getInputStream();
        OutputStream out = client.getOutputStream();

        StringBuilder request = new StringBuilder();
        int c;
        while ((c = in.read()) != -1 && c != '\r') {
            if (c == '\n' || c == ' ') break;
            request.append((char) c);
        }

        String[] parts = request.toString().split(" ");
        String method = parts[0];
        String url = parts[1];

        Map<String, String> params = parseQuery(url);

        if (!params.containsKey("payload")) {
            sendResponse(out, "Error: payload parameter is missing", 400);
        } else {
            try {
                Yaml yaml = new Yaml();
                Map<String, Object> data = yaml.load(params.get("payload"));
                if ("Create".equals(data.get("type"))) {
                    sendResponse(out, "Error: Type 'Create' not allowed", 400);
                } else {
                    sendResponse(out, "Success", 200);
                }
            } catch (Exception e) {
                sendResponse(out, "Error: Invalid YAML payload", 400);
            }
        }

        client.close();
    }

    private static Map<String, String> parseQuery(String url) {
        int queryIndex = url.indexOf('?');
        if (queryIndex == -1) return Map.of();
        String query = url.substring(queryIndex + 1);
        String[] pairs = query.split("&");
        Map<String, String> params = new java.util.HashMap<>();
        for (String pair : pairs) {
            String[] keyValue = pair.split("=");
            if (keyValue.length == 2) {
                params.put(keyValue[0], keyValue[1]);
            }
        }
        return params;
    }

    private static void sendResponse(OutputStream out, String message, int status) throws IOException {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(status).append(" OK\r\n");
        response.append("Content-Type: text/plain\r\n");
        response.append("\r\n");
        response.append(message);
        out.write(response.toString().getBytes());
        out.flush();
    }
}