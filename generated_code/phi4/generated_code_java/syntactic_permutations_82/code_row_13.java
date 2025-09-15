import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/getPayload", new PayloadHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class PayloadHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> payloadMap = parseQuery(query);

            if (payloadMap.containsKey("name")) {
                String response = "Name: " + payloadMap.get("name");
                sendResponse(exchange, 200, response);
            } else {
                sendResponse(exchange, 400, "Name parameter is missing.");
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> map = new HashMap<>();
            if (query != null) {
                StringTokenizer tokenizer = new StringTokenizer(query, "&");
                while (tokenizer.hasMoreTokens()) {
                    String[] param = tokenizer.nextToken().split("=");
                    if (param.length == 2) {
                        map.put(param[0], param[1]);
                    }
                }
            }
            return map;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
