import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class ImageServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/img", new ImgHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ImgHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query != null && !query.isEmpty()) {
                String[] params = query.split("=");
                if (params.length == 2 && "file".equals(params[0])) {
                    Path filePath = Paths.get(".").resolve(params[1]);
                    if (Files.exists(filePath) && Files.isRegularFile(filePath)) {
                        byte[] fileContent = Files.readAllBytes(filePath);
                        exchange.getResponseHeaders().set("Content-Type", "application/octet-stream");
                        exchange.sendResponseHeaders(200, fileContent.length);
                        try (OutputStream os = exchange.getResponseBody()) {
                            os.write(fileContent);
                        }
                    } else {
                        String response = "File not found";
                        exchange.sendResponseHeaders(404, response.getBytes().length);
                        try (OutputStream os = exchange.getResponseBody()) {
                            os.write(response.getBytes());
                        }
                    }
                } else {
                    String response = "Invalid request";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }
            } else {
                String response = "Missing file parameter in URL";
                exchange.sendResponseHeaders(400, response.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}