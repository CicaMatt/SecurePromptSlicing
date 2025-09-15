import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class TemperatureAPI {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                java.util.Map<String, String> params = java.net.URLDecoder.decode(query, "UTF-8")
                        .split("&").stream()
                        .map(param -> param.split("="))
                        .filter(parts -> parts.length == 2)
                        .collect(java.util.stream.Collectors.toMap(parts -> parts[0], parts -> parts[1]));

                String latitude = params.get("latitude");
                String longitude = params.get("longitude");
                String date = params.get("date");

                if (latitude != null && longitude != null && date != null) {
                    try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                        String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
                        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                            stmt.setString(1, latitude);
                            stmt.setString(2, longitude);
                            stmt.setString(3, date);

                            try (ResultSet rs = stmt.executeQuery()) {
                                if (rs.next()) {
                                    String temperature = rs.getString("temperature");
                                    exchange.sendResponseHeaders(200, temperature.length());
                                    java.io.OutputStream os = exchange.getResponseBody();
                                    os.write(temperature.getBytes());
                                    os.close();
                                } else {
                                    String response = "Temperature data not found";
                                    exchange.sendResponseHeaders(404, response.length());
                                    exchange.getResponseBody().write(response.getBytes());
                                    exchange.getResponseBody().close();
                                }
                            }
                        }
                    } catch (Exception e) {
                        String response = "Internal Server Error: " + e.getMessage();
                        exchange.sendResponseHeaders(500, response.length());
                        exchange.getResponseBody().write(response.getBytes());
                        exchange.getResponseBody().close();
                    }
                } else {
                    String response = "Missing parameters";
                    exchange.sendResponseHeaders(400, response.length());
                    exchange.getResponseBody().write(response.getBytes());
                    exchange.getResponseBody().close();
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                exchange.getResponseBody().write(response.getBytes());
                exchange.getResponseBody().close();
            }
        }
    }
}
