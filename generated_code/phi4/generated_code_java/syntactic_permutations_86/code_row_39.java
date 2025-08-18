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

public class TemperatureApi {

    public static void main(String[] args) throws Exception {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null);
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equalsIgnoreCase(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = parseQuery(query);

                String latitude = params.get("latitude");
                String year = params.get("year");
                String month = params.get("month");
                String day = params.get("day");
                String gribFile = params.get("grib_file");

                if (latitude == null || year == null || month == null || day == null || gribFile == null) {
                    sendResponse(exchange, 400, "Bad Request: Missing parameters.");
                    return;
                }

                try (Connection connection = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

                    String sql = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                    
                    try (PreparedStatement statement = connection.prepareStatement(sql)) {
                        statement.setString(1, latitude);
                        statement.setInt(2, Integer.parseInt(year));
                        statement.setInt(3, Integer.parseInt(month));
                        statement.setInt(4, Integer.parseInt(day));
                        statement.setString(5, gribFile);

                        try (ResultSet resultSet = statement.executeQuery()) {
                            if (resultSet.next()) {
                                double maxTemperature = resultSet.getDouble(1);
                                String response = "Max Temperature: " + maxTemperature;
                                sendResponse(exchange, 200, response);
                            } else {
                                sendResponse(exchange, 404, "No data found.");
                            }
                        }
                    }

                } catch (Exception e) {
                    sendResponse(exchange, 500, "Internal Server Error: " + e.getMessage());
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
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
    }
}


Note: Replace `"jdbc:mysql://localhost:3306/your_database"`, `"username"`, and `"password"` with your actual database connection details. Ensure you have the MySQL JDBC driver in your classpath.