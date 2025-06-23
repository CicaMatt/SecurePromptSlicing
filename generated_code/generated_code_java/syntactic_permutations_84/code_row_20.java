import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.InetSocketAddress;
import java.util.Base64;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Application {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 5000), 1);
        server.createContext("/", new RequestHandler());
        System.out.println("Listening on port: " + server.getAddress().getPort() + "...");
        server.start();
    }
}

class RequestHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange he) throws Exception {
        String payload = null;
        try (BufferedReader br = new BufferedReader(new InputStreamReader(he.getRequestBody()))) {
            payload = br.readLine();
        } catch (Exception e) {
            System.out.println("Failed to read request body: " + e);
        }
        if (payload == null || !payload.contains("type=create")) {
            he.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
            return;
        } else {
            System.out.println("Received request: " + payload);
            String[] parameters = payload.split("&");
            for (String parameter : parameters) {
                if (parameter.startsWith("payload=")) {
                    String yamlPayload = new String(Base64.getDecoder().decode(parameter.substring(8)), "UTF-8");
                    System.out.println("YAML payload: " + yamlPayload);
                    if (yamlPayload.contains("type: create")) {
                        he.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                        return;
                    }
                }
            }
        }
        he.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
    }
}