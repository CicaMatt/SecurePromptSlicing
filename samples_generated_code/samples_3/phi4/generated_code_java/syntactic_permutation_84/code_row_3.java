import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class PayloadChecker {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.contains("payload")) {
                String response = "Error: No payload parameter found.";
                sendResponse(exchange, 400, response);
                return;
            }

            ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
            try {
                Payload payload = mapper.readValue(exchange.getRequestBody().readAllBytes(), Payload.class);

                if ("Create".equals(payload.getType())) {
                    String response = "Error: Create type is not allowed.";
                    sendResponse(exchange, 400, response);
                    return;
                }

                String response = "Payload received successfully.";
                sendResponse(exchange, 200, response);
            } catch (IOException e) {
                sendResponse(exchange, 500, "Error processing payload.");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }

    static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


Note: This code uses `com.fasterxml.jackson.dataformat.yaml.YAMLFactory` for YAML parsing, which requires the Jackson library. Make sure to include the following Maven dependency in your `pom.xml` if you're using Maven:


<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.13.3</version>
</dependency>
<dependency>
    <groupId>com.fasterxml.jackson.dataformat</groupId>
    <artifactId>jackson-dataformat-yaml</artifactId>
    <version>2.13.3</version>
</dependency>