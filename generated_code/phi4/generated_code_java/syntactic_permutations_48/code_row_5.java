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
        server.createContext("/img", new ImgHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server is listening on port 8000");
    }

    static class ImgHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String fileParam = query.split("file=")[1];
                try (InputStream is = ImageServer.class.getClassLoader().getResourceAsStream(fileParam)) {
                    if (is == null) {
                        String response = "File not found";
                        exchange.sendResponseHeaders(404, response.length());
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    } else {
                        exchange.getResponseHeaders().set("Content-Type", getContentType(fileParam));
                        exchange.sendResponseHeaders(200, is.available());

                        try (OutputStream os = exchange.getResponseBody()) {
                            byte[] buffer = new byte[is.available()];
                            is.read(buffer);
                            os.write(buffer);
                        }
                    }
                } catch (Exception e) {
                    String response = "Internal server error";
                    exchange.sendResponseHeaders(500, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method not allowed";
                exchange.sendResponseHeaders(405, response.length());
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }

        private String getContentType(String filename) {
            if (filename.endsWith(".png")) return "image/png";
            else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) return "image/jpeg";
            else if (filename.endsWith(".gif")) return "image/gif";
            else if (filename.endsWith(".bmp")) return "image/bmp";
            else return "application/octet-stream";
        }
    }
}