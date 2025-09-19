import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class PingDecorator {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(null, 8000);
        String contextPath = "/ping";
        server.createContext(contextPath, new PingHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class PingHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                if (query != null) {
                    String url = URLDecoder.decode(query.split("=")[1], StandardCharsets.UTF_8.toString());
                    String response = pingUrl(url);
                    exchange.sendResponseHeaders(200, response.getBytes().length);
                    exchange.getResponseBody().write(response.getBytes());
                    exchange.close();
                }
            }
        }

        private String pingUrl(String url) {
            StringBuilder output = new StringBuilder();
            Process p;
            try {
                p = Runtime.getRuntime().exec("ping " + url);
                BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
            } catch (Exception e) {
                output.append("Error: ").append(e.getMessage());
            }
            return output.toString();
        }
    }
}