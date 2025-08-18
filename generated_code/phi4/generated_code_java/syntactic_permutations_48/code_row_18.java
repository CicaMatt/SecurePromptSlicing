import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

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
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = splitQuery(query);
                
                String fileName = params.get("file");
                if (fileName != null && !fileName.isEmpty()) {
                    File file = new File(fileName);
                    if (file.exists() && file.isFile()) {
                        byte[] fileContent = Files.readAllBytes(file.toPath());
                        exchange.sendResponseHeaders(200, fileContent.length);

                        OutputStream os = exchange.getResponseBody();
                        os.write(fileContent);
                        os.close();
                    } else {
                        String response = "File not found";
                        exchange.sendResponseHeaders(404, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    }
                } else {
                    String response = "File parameter is missing";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> splitQuery(String query) {
            Map<String, String> result = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        result.put(entry[0], java.net.URLDecoder.decode(entry[1], "UTF-8"));
                    } else {
                        result.put(entry[0], "");
                    }
                }
            }
            return result;
        }
    }
}