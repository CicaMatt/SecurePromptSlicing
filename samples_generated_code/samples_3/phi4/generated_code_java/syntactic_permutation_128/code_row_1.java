import java.io.*;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int serverPort = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(serverPort), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String username = "World";
                
                if (query != null && !query.isEmpty()) {
                    String[] params = query.split("=");
                    if (params.length > 1) {
                        username = params[1];
                    }
                }

                String responseText = "Hello, " + username;
                exchange.sendResponseHeaders(200, responseText.getBytes().length);
                
                OutputStream os = exchange.getResponseBody();
                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os));
                writer.write(responseText);
                writer.close();
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }
    }
}