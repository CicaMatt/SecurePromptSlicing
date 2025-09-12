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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/temperature_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null);
        server.start();
        System.out.println("Server is listening on port " + port);
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> params = parseQueryParams(exchange.getRequestURI().getQuery());
                
                double latitude = Double.parseDouble(params.get("latitude"));
                double longitude = Double.parseDouble(params.get("longitude"));
                String date = params.get("date");
                
                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        stmt.setDouble(1, latitude);
                        stmt.setDouble(2, longitude);
                        stmt.setString(3, date);

                        ResultSet rs = stmt.executeQuery();
                        if (rs.next()) {
                            String temperature = rs.getString("temperature");
                            sendResponse(exchange, 200, temperature);
                        } else {
                            sendResponse(exchange, 404, "Temperature not found");
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    sendResponse(exchange, 500, "Internal server error");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, String> parseQueryParams(String query) {
            Map<String, String> params = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] pair = param.split("=");
                    if (pair.length == 2) {
                        params.put(pair[0], pair[1]);
                    }
                }
            }
            return params;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}