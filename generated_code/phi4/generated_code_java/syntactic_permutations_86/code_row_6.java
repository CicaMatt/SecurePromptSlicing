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
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;
import org.json.JSONObject;

public class TemperatureService {

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
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = new HashMap<>();
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        queryParams.put(entry[0], entry[1]);
                    } else {
                        queryParams.put(entry[0], "");
                    }
                }

                JSONObject jsonResponse = new JSONObject();
                try {
                    double latitude = Double.parseDouble(queryParams.getOrDefault("latitude", "0"));
                    double longitude = Double.parseDouble(queryParams.getOrDefault("longitude", "0"));
                    int year = Integer.parseInt(queryParams.getOrDefault("year", "0"));
                    int month = Integer.parseInt(queryParams.getOrDefault("month", "0"));
                    int day = Integer.parseInt(queryParams.getOrDefault("day", "0"));
                    String gribFile = queryParams.getOrDefault("grib_file", "");

                    double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);
                    jsonResponse.put("max_temperature", maxTemperature);
                } catch (Exception e) {
                    jsonResponse.put("error", "Invalid parameters");
                }

                String response = jsonResponse.toString();
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "root";
            String password = "password";

            String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (Connection conn = DriverManager.getConnection(url, user, password);
                 PreparedStatement stmt = conn.prepareStatement(query)) {

                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setInt(3, year);
                stmt.setInt(4, month);
                stmt.setInt(5, day);
                stmt.setString(6, gribFile);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble(1);
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }

            return Double.NaN; // Return NaN if no result is found
        }
    }
}
