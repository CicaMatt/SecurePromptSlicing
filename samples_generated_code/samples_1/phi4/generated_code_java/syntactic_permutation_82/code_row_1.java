import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = parseQuery(query);
                
                String nameValue = queryParams.getOrDefault("name", "Name not found");
                String responseText = "Name: " + nameValue;

                exchange.sendResponseHeaders(200, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            } else {
                String responseText = "Method Not Allowed";
                exchange.sendResponseHeaders(405, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] keyValue = param.split("=");
                    if (keyValue.length == 2) {
                        queryParams.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return queryParams;
        }
    }
}