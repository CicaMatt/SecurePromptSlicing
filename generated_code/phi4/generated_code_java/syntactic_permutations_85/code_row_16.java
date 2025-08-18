import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TemperatureService {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", (exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                try {
                    String payload = new String(exchange.getRequestBody().readAllBytes());
                    double latitude = extractValue(payload, "latitude");
                    double longitude = extractValue(payload, "longitude");

                    double temperature = getTemperatureFromDatabase(latitude, longitude);

                    String response = String.format("{\"temperature\": %.2f}", temperature);
                    exchange.sendResponseHeaders(200, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } catch (Exception e) {
                    String response = "{\"error\":\"" + e.getMessage() + "\"}";
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
            exchange.close();
        }));
        server.setExecutor(null);
        server.start();
    }

    private static double extractValue(String payload, String key) throws IOException {
        String[] parts = payload.split("&");
        for (String part : parts) {
            String[] keyValue = part.split("=");
            if (key.equals(keyValue[0])) {
                return Double.parseDouble(keyValue[1]);
            }
        }
        throw new IllegalArgumentException("Key not found: " + key);
    }

    private static double getTemperatureFromDatabase(double latitude, double longitude) throws Exception {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String username = "root"; // Replace with your database username
        String password = ""; // Replace with your database password

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getDouble("temperature");
                    } else {
                        throw new IllegalArgumentException("No data found for the given coordinates.");
                    }
                }
            }
        }
    }
}


Note: You need to have MySQL JDBC driver in your classpath. Replace `username` and `password` with actual database credentials. Also, ensure that the table `sensor_data` exists and has columns `latitude`, `longitude`, and `temperature`.