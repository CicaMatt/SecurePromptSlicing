import java.io.*;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            InputStreamReader isr = new InputStreamReader(exchange.getRequestBody());
            BufferedReader br = new BufferedReader(isr);
            StringBuilder requestText = new StringBuilder();
            String line;
            while ((line = br.readLine()) != null) {
                requestText.append(line + "\n");
            }
            
            String username = extractUsername(requestText.toString());

            String responseText = "hello " + username;
            exchange.sendResponseHeaders(200, responseText.length());
            OutputStream os = exchange.getResponseBody();
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os));
            writer.write(responseText);
            writer.close();
            os.close();
        }

        private String extractUsername(String request) {
            // Assuming the request contains a simple parameter like "username=johndoe"
            if (request.contains("username=")) {
                int start = request.indexOf("username=") + 9;
                int end = request.indexOf(' ', start);
                if (end == -1) {
                    end = request.length();
                }
                return request.substring(start, end);
            }
            return "unknown";
        }
    }
}