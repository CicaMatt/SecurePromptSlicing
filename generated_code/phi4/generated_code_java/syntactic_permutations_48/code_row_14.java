import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
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
                java.util.Map<String, String> params = parseQuery(query);
                String fileParam = params.get("file");

                if (fileParam != null && !fileParam.isEmpty()) {
                    byte[] imageData = Files.readAllBytes(Paths.get(fileParam));
                    exchange.getResponseHeaders().set("Content-Type", "image/jpeg");
                    exchange.sendResponseHeaders(200, imageData.length);

                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(imageData);
                    }
                } else {
                    String response = "File parameter is missing or empty";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }

            exchange.close();
        }

        private java.util.Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) {
                return java.util.Collections.emptyMap();
            }
            java.util.HashMap<String, String> result = new java.util.HashMap<>();
            String[] pairs = query.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                try {
                    result.put(idx > 0 ? pair.substring(0, idx)
                            : pair,
                            idx > 0 && pair.length() > idx + 1
                                    ? pair.substring(idx + 1)
                                    : "");
                } catch (java.lang.Exception e) {
                    // Ignore errors
                }
            }
            return result;
        }
    }
}


Make sure you have the necessary permissions and file paths correctly set to read the files from your server's directory. Also, ensure that your Java environment supports `com.sun.net.httpserver.HttpServer`, which is part of the standard library in JDK 1.6 and later but considered a part of the non-standard API.