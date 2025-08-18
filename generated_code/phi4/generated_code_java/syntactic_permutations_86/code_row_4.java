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
import java.util.StringJoiner;

public class TemperatureWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server is listening on port 8080");
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = parseQuery(query);

                String latitude = params.get("latitude");
                String longitude = params.get("longitude");
                String year = params.get("year");
                String month = params.get("month");
                String day = params.get("day");
                String gribFile = params.get("grib_file");

                if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
                    sendResponse(exchange, 400, "Missing parameters");
                    return;
                }

                try {
                    double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);
                    String response = "Max Temperature: " + maxTemperature;
                    sendResponse(exchange, 200, response);
                } catch (Exception e) {
                    sendResponse(exchange, 500, "Internal Server Error");
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

        private double getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) throws Exception {
            Connection connection = null;
            PreparedStatement statement = null;
            ResultSet resultSet = null;

            try {
                connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
                String sql = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                statement = connection.prepareStatement(sql);
                statement.setString(1, latitude);
                statement.setString(2, longitude);
                statement.setInt(3, Integer.parseInt(year));
                statement.setInt(4, Integer.parseInt(month));
                statement.setInt(5, Integer.parseInt(day));
                statement.setString(6, gribFile);

                resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getDouble(1);
                } else {
                    throw new Exception("No temperature data found");
                }
            } finally {
                if (resultSet != null) resultSet.close();
                if (statement != null) statement.close();
                if (connection != null) connection.close();
            }
        }
    }
}