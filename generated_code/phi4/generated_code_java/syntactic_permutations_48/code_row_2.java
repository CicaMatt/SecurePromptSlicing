import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

public class ImageServer {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/img", new ImageHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class ImageHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String fileParam = "";
            if (query != null && !query.isEmpty()) {
                for (String param : query.split("&")) {
                    String[] keyValue = param.split("=");
                    if ("file".equals(keyValue[0])) {
                        fileParam = keyValue.length > 1 ? keyValue[1] : "";
                        break;
                    }
                }
            }

            if (fileParam.isEmpty()) {
                exchange.sendResponseHeaders(400, -1); // Bad Request
                return;
            }

            File imageFile = new File(fileParam);
            if (!imageFile.exists() || !imageFile.isFile()) {
                exchange.sendResponseHeaders(404, -1); // Not Found
                return;
            }

            byte[] imageData = Files.readAllBytes(imageFile.toPath());
            String mimeType = Files.probeContentType(imageFile.toPath());

            if (mimeType == null) {
                mimeType = "application/octet-stream";
            }

            exchange.getResponseHeaders().set("Content-Type", mimeType);
            exchange.sendResponseHeaders(200, imageData.length);

            try (OutputStream os = exchange.getResponseBody()) {
                os.write(imageData);
            }
        }
    }
}