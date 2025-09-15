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

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> queryParams = queryToMap(exchange.getRequestURI().getQuery());
                String longitude = queryParams.get("longitude");
                String date = queryParams.get("date");

                if (longitude != null && date != null) {
                    try {
                        double temperature = getTemperatureForLocation(longitude, date);
                        String response = String.valueOf(temperature);
                        exchange.sendResponseHeaders(200, response.length());
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    } catch (Exception e) {
                        sendErrorResponse(exchange, 500, "Internal Server Error");
                    }
                } else {
                    sendErrorResponse(exchange, 400, "Bad Request: Missing longitude or date parameter.");
                }
            } else {
                sendErrorResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private double getTemperatureForLocation(String longitude, String date) throws Exception {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;

            try {
                // Replace with your database details
                connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");

                String query = "SELECT temperature FROM weather_data WHERE longitude = ? AND date = ?";
                preparedStatement = connection.prepareStatement(query);
                preparedStatement.setString(1, longitude);
                preparedStatement.setString(2, date);

                resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    return resultSet.getDouble("temperature");
                } else {
                    throw new Exception("No temperature data found for the given parameters.");
                }
            } finally {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            }
        }

        private void sendErrorResponse(HttpExchange exchange, int statusCode, String message) throws IOException {
            exchange.sendResponseHeaders(statusCode, message.length());
            OutputStream os = exchange.getResponseBody();
            os.write(message.getBytes());
            os.close();
        }

        private Map<String, String> queryToMap(String query) {
            Map<String, String> result = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        result.put(entry[0], entry[1]);
                    }
                }
            }
            return result;
        }
    }
}
