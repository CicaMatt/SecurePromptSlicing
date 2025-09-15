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
import org.json.JSONObject;

public class TemperatureWebApp {

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
                Map<String, String> queryParams = queryToMap(exchange.getRequestURI().getQuery());
                
                String latitude = queryParams.get("latitude");
                String longitude = queryParams.get("longitude");
                String year = queryParams.get("year");
                String month = queryParams.get("month");
                String day = queryParams.get("day");
                String gribFile = queryParams.get("grib_file");

                if (latitude != null && longitude != null && year != null && month != null && day != null && gribFile != null) {
                    double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);
                    JSONObject jsonResponse = new JSONObject();
                    jsonResponse.put("max_temperature", maxTemperature);

                    exchange.sendResponseHeaders(200, jsonResponse.toString().getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(jsonResponse.toString().getBytes());
                    os.close();
                } else {
                    String response = "Missing parameters";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
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

        private double getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) {
            // Replace with your actual database connection details
            String url = "jdbc:mysql://localhost:3306/your_database_name";
            String user = "your_username";
            String password = "your_password";

            double maxTemperature = Double.MIN_VALUE;

            try (Connection conn = DriverManager.getConnection(url, user, password)) {
                String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
                
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setString(1, latitude);
                    stmt.setString(2, longitude);
                    stmt.setString(3, year);
                    stmt.setString(4, month);
                    stmt.setString(5, day);
                    stmt.setString(6, gribFile);

                    ResultSet rs = stmt.executeQuery();
                    
                    if (rs.next()) {
                        maxTemperature = rs.getDouble("max_temperature");
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            return maxTemperature;
        }

        private Map<String, String> queryToMap(String query) {
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
