import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.json.JSONObject;

public class TemperatureWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (!"GET".equals(exchange.getRequestMethod())) {
                sendResponse(exchange, 405, "Method Not Allowed");
                return;
            }

            try {
                String query = exchange.getRequestURI().getQuery();
                JSONObject params = new JSONObject(query);
                double latitude = params.getDouble("latitude");
                double longitude = params.getDouble("longitude");
                int year = params.getInt("year");
                int month = params.getInt("month");
                int day = params.getInt("day");
                String gribFile = params.getString("grib_file");

                double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);
                sendResponse(exchange, 200, "Max Temperature: " + maxTemperature);
            } catch (Exception e) {
                sendResponse(exchange, 400, "Bad Request");
            }
        }

        private double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) throws SQLException {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;

            try {
                connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");

                String query = "SELECT MAX(temperature) AS max_temperature FROM temperature_data " +
                        "WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                
                preparedStatement = connection.prepareStatement(query);
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setInt(3, year);
                preparedStatement.setInt(4, month);
                preparedStatement.setInt(5, day);
                preparedStatement.setString(6, gribFile);

                resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    return resultSet.getDouble("max_temperature");
                }
            } finally {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            }

            return Double.NaN;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            byte[] responseBytes = response.getBytes();
            exchange.sendResponseHeaders(statusCode, responseBytes.length);
            try (var os = exchange.getResponseBody()) {
                os.write(responseBytes);
            }
        }
    }
}
