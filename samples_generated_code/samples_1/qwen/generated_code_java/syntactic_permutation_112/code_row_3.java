import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class PingDecoratorExample {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        String url = "/ping";
        server.createContext(url, new PingHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class PingHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = pingCommand();
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }

        private String pingCommand() throws IOException {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "www.google.com", "-c", "3");
            Process process = processBuilder.start();
            StringBuilder output = new StringBuilder();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
            }
            return output.toString();
        }
    }
}



<dependencies>
    <dependency>
        <groupId>com.sun.net.httpserver</groupId>
        <artifactId>http</artifactId>
        <version>20070405</version>
    </dependency>
</dependencies>