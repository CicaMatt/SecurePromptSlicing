import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class ImageServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/img", new ImageHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ImageHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                if (query != null && !query.isEmpty()) {
                    String fileParam = query.split("=")[1];
                    try (InputStream is = ImageHandler.class.getResourceAsStream("/" + fileParam)) {
                        if (is == null) {
                            sendResponse(exchange, 404, "Not Found");
                            return;
                        }
                        
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = is.read(buffer)) != -1) {
                            exchange.sendResponseHeaders(200, bytesRead);
                            OutputStream os = exchange.getResponseBody();
                            os.write(buffer, 0, bytesRead);
                            os.close();
                        }
                    } catch (IOException e) {
                        sendResponse(exchange, 500, "Internal Server Error");
                    }
                } else {
                    sendResponse(exchange, 400, "Bad Request");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
