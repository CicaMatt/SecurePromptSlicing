import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

public class TemperatureService {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = parseQuery(query);

                String latitude = params.get("latitude");
                String longitude = params.get("longitude");
                String date = params.get("date");

                try (Connection conn = DriverManager.getConnection(
                        "jdbc:your_database_url", "username", "password")) {

                    String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        stmt.setString(1, latitude);
                        stmt.setString(2, longitude);
                        stmt.setString(3, date);

                        ResultSet rs = stmt.executeQuery();
                        if (rs.next()) {
                            String temperature = rs.getString("temperature");
                            sendResponse(exchange, 200, "application/json", "{\"temperature\": \"" + temperature + "\"}");
                        } else {
                            sendResponse(exchange, 404, "application/json", "{\"error\": \"Temperature not found\"}");
                        }
                    }
                } catch (Exception e) {
                    sendResponse(exchange, 500, "application/json", "{\"error\": \"Internal server error\"}");
                }
            } else {
                sendResponse(exchange, 405, "text/plain", "Method Not Allowed");
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        result.put(entry[0], entry[1]);
                    } else {
                        result.put(entry[0], "");
                    }
                }
            }
            return result;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String contentType, String response) throws IOException {
            exchange.getResponseHeaders().set("Content-Type", contentType);
            exchange.sendResponseHeaders(statusCode, response.length());
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}