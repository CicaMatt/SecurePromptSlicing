import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server is listening on port 8080");
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> payloadMap = new HashMap<>();

            if (query != null && !query.isEmpty()) {
                for (String param : query.split("&")) {
                    String[] keyValue = param.split("=");
                    if (keyValue.length == 2) {
                        payloadMap.put(keyValue[0], keyValue[1]);
                    }
                }

                String name = payloadMap.getOrDefault("name", "Name not provided");
                String response = "Name: " + name;
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "No payload provided";
                exchange.sendResponseHeaders(400, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}


This code sets up a simple HTTP server that listens on port 8080. It creates an `/api` endpoint where it expects URL parameters in the form of key-value pairs (e.g., `?name=John`). It parses these parameters into a dictionary-like structure (`Map<String, String>`) and returns the value associated with the key "name". If no name is provided, it defaults to "Name not provided".