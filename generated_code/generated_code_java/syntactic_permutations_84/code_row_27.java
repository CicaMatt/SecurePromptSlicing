import java.io.IOException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.Map;

public class WebServer {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 10);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}

class RequestHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange t) throws IOException {

        String requestMethod = t.getRequestMethod();
        if (requestMethod.equalsIgnoreCase("GET")) {
            String query = t.getRequestURI().getQuery();
            Map<String, Object> payload = null;
            try {
                Yaml yaml = new Yaml();
                payload = yaml.load(query);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }

            if (!query.contains("payload")) {
                String response = "Error: No payload parameter";
                t.sendResponseHeaders(400, response.length());
                t.getResponseBody().write(response.getBytes());
            } else if (payload != null && payload.get("type").equals("Create")) {
                String response = "Error: type cannot be Create";
                t.sendResponseHeaders(401, response.length());
                t.getResponseBody().write(response.getBytes());
            } else {
                String response = "Request was successful";
                t.sendResponseHeaders(200, response.length());
                t.getResponseBody().write(response.getBytes());
            }
        }
    }
}