import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.concurrent.Executors;

public class PingDecorator {

    private static String url = "www.example.com"; // URL to ping

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/ping", new PingHandler());
        server.setExecutor(Executors.newCachedThreadPool()); // creates a default executor
        server.start();
    }

    static class PingHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = executePingCommand(url);
            sendResponse(exchange, 200, response);
        }
        
        private String executePingCommand(String urlToPing) {
            try {
                ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", urlToPing); // Use -n for Windows
                Process process = processBuilder.start();
                
                StringBuilder output = new StringBuilder();
                byte[] buffer = new byte[1024];
                int read;
                
                while ((read = process.getInputStream().read(buffer)) != -1) {
                    output.append(new String(buffer, 0, read));
                }
                
                return output.toString();
            } catch (IOException e) {
                return "Failed to execute ping command: " + e.getMessage();
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}