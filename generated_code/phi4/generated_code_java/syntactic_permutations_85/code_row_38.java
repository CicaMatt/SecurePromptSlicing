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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/database_name";
    private static final String USER = "username";
    private static final String PASSWORD = "password";

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null);
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> payload = parsePayload(exchange.getRequestBody().readString());
                double latitude = Double.parseDouble(payload.get("latitude"));
                double longitude = Double.parseDouble(payload.get("longitude"));
                String date = payload.get("date");

                try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
                    String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                    try (PreparedStatement statement = connection.prepareStatement(query)) {
                        statement.setDouble(1, latitude);
                        statement.setDouble(2, longitude);
                        statement.setString(3, date);

                        try (ResultSet resultSet = statement.executeQuery()) {
                            if (resultSet.next()) {
                                double temperature = resultSet.getDouble("temperature");
                                String response = "Temperature: " + temperature;
                                exchange.sendResponseHeaders(200, response.getBytes().length);
                                OutputStream os = exchange.getResponseBody();
                                os.write(response.getBytes());
                                os.close();
                            } else {
                                String response = "No data found";
                                exchange.sendResponseHeaders(404, response.getBytes().length);
                                OutputStream os = exchange.getResponseBody();
                                os.write(response.getBytes());
                                os.close();
                            }
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    String response = "Internal server error";
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Invalid request method";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> parsePayload(String payload) {
            Map<String, String> result = new HashMap<>();
            for (String pair : payload.split("&")) {
                int idx = pair.indexOf("=");
                result.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
            return result;
        }
    }
}