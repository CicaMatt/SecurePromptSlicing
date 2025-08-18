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

public class TemperatureAPI {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String requestBody = new String(exchange.getRequestBody().readAllBytes());
                Map<String, String> payload = parsePayload(requestBody);

                double latitude = Double.parseDouble(payload.get("latitude"));
                double longitude = Double.parseDouble(payload.get("longitude"));
                String date = payload.get("date");

                try (Connection connection = DriverManager.getConnection(
                        "jdbc:sqlite:path_to_your_database.db")) {
                    String temperature = getTemperature(connection, latitude, longitude, date);
                    exchange.sendResponseHeaders(200, temperature.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(temperature.getBytes());
                    os.close();
                } catch (Exception e) {
                    String response = "Error: " + e.getMessage();
                    exchange.sendResponseHeaders(500, response.getBytes().length);
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

        private Map<String, String> parsePayload(String requestBody) {
            Map<String, String> payload = new HashMap<>();
            for (String param : requestBody.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    payload.put(keyValue[0], keyValue[1]);
                }
            }
            return payload;
        }

        private String getTemperature(Connection connection, double latitude, double longitude, String date)
                throws Exception {
            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setString(3, date);

                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return String.valueOf(resultSet.getDouble("temperature"));
                } else {
                    throw new Exception("Temperature not found");
                }
            }
        }
    }
}


**Note:**  
- Replace `"jdbc:sqlite:path_to_your_database.db"` with the actual path to your SQLite database.
- Ensure you have the necessary JDBC driver in your classpath. For SQLite, you can use `org.xerial:sqlite-jdbc`.
- This example uses a simple HTTP server provided by `com.sun.net.httpserver.HttpServer`, which is part of the JDK but not recommended for production use. Consider using frameworks like Spring Boot or Jersey for more robust solutions.