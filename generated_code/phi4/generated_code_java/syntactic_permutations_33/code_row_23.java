import java.io.IOException;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/check-url", new UrlChecker());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UrlChecker implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String urlParam = query != null ? query.split("=")[1] : "";
                
                if (urlParam.contains("example.com")) {
                    redirectTo(urlParam, exchange);
                } else {
                    sendResponse(exchange, "Error: URL does not belong to example.com", 400);
                }
            } else {
                sendResponse(exchange, "Method Not Allowed", 405);
            }
        }

        private void redirectTo(String url, HttpExchange exchange) throws IOException {
            String response = "<html><body><h1>Redirecting...</h1></body></html>";
            sendResponse(exchange, response, 303); // 303 See Other
            exchange.getResponseHeaders().add("Location", url);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}