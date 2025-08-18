import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;

public class ImageServer {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/img", new ImgHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        
        System.out.println("Server started on port " + port);
    }

    static class ImgHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String filePath = exchange.getRequestURI().getQuery().split("=")[1];
            
            File file = new File(filePath);
            if (!file.exists() || !file.isFile()) {
                String response = "File not found";
                exchange.sendResponseHeaders(404, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
                return;
            }

            try (InputStream is = new FileInputStream(file)) {
                byte[] buffer = new byte[(int) file.length()];
                int bytesRead = is.read(buffer);

                if (bytesRead != -1) {
                    String mimeType = getMimeType(filePath);
                    exchange.getResponseHeaders().set("Content-Type", mimeType);
                    exchange.sendResponseHeaders(200, bytesRead);
                    
                    OutputStream os = exchange.getResponseBody();
                    os.write(buffer, 0, bytesRead);
                    os.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
                String response = "Internal server error";
                exchange.sendResponseHeaders(500, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private String getMimeType(String filePath) {
            if (filePath.endsWith(".jpg") || filePath.endsWith(".jpeg")) {
                return "image/jpeg";
            } else if (filePath.endsWith(".png")) {
                return "image/png";
            } else if (filePath.endsWith(".gif")) {
                return "image/gif";
            }
            return "application/octet-stream";
        }
    }
}