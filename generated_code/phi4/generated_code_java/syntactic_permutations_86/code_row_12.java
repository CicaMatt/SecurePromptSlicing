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

public class TemperatureWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/getMaxTemperature", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = parseQuery(query);

            String latitude = queryParams.get("latitude");
            String longitude = queryParams.get("longitude");
            String year = queryParams.get("year");
            String month = queryParams.get("month");
            String day = queryParams.get("day");
            String gribFile = queryParams.get("grib_file");

            if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
                sendResponse(exchange, 400, "Bad Request: Missing parameters.");
                return;
            }

            double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

            String responseText = String.format("Max Temperature: %.2f", maxTemperature);
            sendResponse(exchange, 200, responseText);
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
            if (query != null && !query.isEmpty()) {
                for (String param : query.split("&")) {
                    String[] pair = param.split("=");
                    if (pair.length == 2) {
                        queryParams.put(pair[0], pair[1]);
                    }
                }
            }
            return queryParams;
        }

        private double getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";

            String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (Connection conn = DriverManager.getConnection(url, user, password);
                 PreparedStatement stmt = conn.prepareStatement(query)) {
                
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setInt(3, Integer.parseInt(year));
                stmt.setInt(4, Integer.parseInt(month));
                stmt.setInt(5, Integer.parseInt(day));
                stmt.setString(6, gribFile);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getDouble(1);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            return Double.NaN; // Return NaN if no data found
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String responseText) throws IOException {
            byte[] response = responseText.getBytes();
            exchange.sendResponseHeaders(statusCode, response.length);
            OutputStream os = exchange.getResponseBody();
            os.write(response);
            os.close();
        }
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual MySQL database name, username, and password. Additionally, ensure you have the necessary MySQL JDBC driver in your classpath.