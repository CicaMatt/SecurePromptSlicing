import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.Executors;

public class ImgServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/img", new ImageHandler());
        server.setExecutor(Executors.newCachedThreadPool()); 
        server.start();
    }

    static class ImageHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String fileParam = "file";
                
                String fileName = "";
                if (query != null && query.startsWith(fileParam + "=")) {
                    fileName = query.substring(fileParam.length() + 1);
                }

                if (!fileName.isEmpty()) {
                    Path path = new File(fileName).toPath();

                    if (Files.exists(path) && !Files.isDirectory(path)) {
                        byte[] fileContent = Files.readAllBytes(path);

                        exchange.getResponseHeaders().add("Content-Type", "application/octet-stream");
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
                    String response = "No file specified";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}