import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class TemperatureService {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> payload = parsePayload(exchange);

                double latitude = Double.parseDouble(payload.get("latitude"));
                double longitude = Double.parseDouble(payload.get("longitude"));
                String date = payload.get("date");

                try (Connection connection = getConnection()) {
                    double temperature = getTemperature(connection, latitude, longitude, date);
                    String response = "Temperature: " + temperature;
                    
                    exchange.sendResponseHeaders(200, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } catch (Exception e) {
                    String response = "Error retrieving temperature";
                    exchange.sendResponseHeaders(500, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Invalid request method";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> parsePayload(HttpExchange exchange) throws IOException {
            Map<String, String> payload = new HashMap<>();
            try (var reader = new java.io.BufferedReader(new java.io.InputStreamReader(exchange.getRequestBody(), StandardCharsets.UTF_8))) {
                for (String line; (line = reader.readLine()) != null;) {
                    String[] keyValue = line.split("=");
                    if (keyValue.length == 2) {
                        payload.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return payload;
        }

        private Connection getConnection() throws Exception {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";

            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection(url, user, password);
        }

        private double getTemperature(Connection connection, double latitude, double longitude, String date)
                throws Exception {
            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setString(3, date);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getDouble("temperature");
                    } else {
                        throw new Exception("Temperature not found for the given location and date.");
                    }
                }
            }
        }
    }
}