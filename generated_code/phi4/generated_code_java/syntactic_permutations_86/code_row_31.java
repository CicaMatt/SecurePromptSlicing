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
import javax.servlet.http.HttpServletRequest;

public class TemperatureWebApp {

    public static void main(String[] args) throws Exception {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> queryParams = queryToMap(exchange.getRequestURI().getQuery());
                try (Connection connection = getDatabaseConnection()) {
                    double maxTemperature = getMaxTemperature(connection, queryParams);
                    String responseText = Double.toString(maxTemperature);

                    exchange.sendResponseHeaders(200, responseText.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } catch (Exception e) {
                    String responseText = "Internal Server Error";
                    exchange.sendResponseHeaders(500, responseText.getBytes().length);
                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(responseText.getBytes());
                    }
                }
            } else {
                String responseText = "Method Not Allowed";
                exchange.sendResponseHeaders(405, responseText.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(responseText.getBytes());
                }
            }
        }

        private Map<String, String> queryToMap(String query) {
            if (query == null || query.isEmpty()) {
                return new HashMap<>();
            }
            Map<String, String> result = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                } else {
                    result.put(entry[0], "");
                }
            }
            return result;
        }

        private Connection getDatabaseConnection() throws Exception {
            String url = "jdbc:mysql://localhost:3306/temperature_db";
            String user = "your_username";
            String password = "your_password";

            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection(url, user, password);
        }

        private double getMaxTemperature(Connection connection, Map<String, String> queryParams) throws Exception {
            String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? " +
                         "AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (PreparedStatement stmt = connection.prepareStatement(sql)) {
                stmt.setDouble(1, Double.parseDouble(queryParams.get("latitude")));
                stmt.setDouble(2, Double.parseDouble(queryParams.get("longitude")));
                stmt.setInt(3, Integer.parseInt(queryParams.get("year")));
                stmt.setInt(4, Integer.parseInt(queryParams.get("month")));
                stmt.setInt(5, Integer.parseInt(queryParams.get("day")));
                stmt.setString(6, queryParams.get("grib_file"));

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble("max_temperature");
                    } else {
                        throw new Exception("No data found for the given parameters.");
                    }
                }
            }
        }
    }
}