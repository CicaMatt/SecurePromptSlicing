import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.json.JSONObject;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class TemperatureApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String payload = new String(exchange.getRequestBody().readAllBytes());
                JSONObject json = new JSONObject(payload);
                
                double latitude = json.getDouble("latitude");
                double longitude = json.getDouble("longitude");
                String date = json.getString("date");

                try (Connection connection = getConnection()) {
                    Double temperature = getTemperature(connection, latitude, longitude, date);
                    String response = temperature != null ? temperature.toString() : "Temperature not found";
                    
                    exchange.sendResponseHeaders(200, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } catch (SQLException e) {
                    String response = "Database error: " + e.getMessage();
                    exchange.sendResponseHeaders(500, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                sendMethodNotAllowed(exchange);
            }
        }

        private void sendMethodNotAllowed(HttpExchange exchange) throws IOException {
            String response = "Method Not Allowed";
            exchange.sendResponseHeaders(405, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    private static Connection getConnection() throws SQLException {
        // Replace with your database connection details
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root";
        String password = "";
        return DriverManager.getConnection(url, user, password);
    }

    private static Double getTemperature(Connection connection, double latitude, double longitude, String date) throws SQLException {
        String query = "SELECT temperature FROM SensorData WHERE latitude = ? AND longitude = ? AND date = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getDouble("temperature");
                }
            }
        }
        return null;
    }
}


Make sure to include the necessary dependencies in your project setup, such as MySQL JDBC driver and JSON library. Adjust database connection details (`url`, `user`, `password`) according to your environment.