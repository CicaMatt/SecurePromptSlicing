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
import java.util.UUID;

public class TemperatureWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = parseQuery(query);
                
                double latitude = Double.parseDouble(params.get("latitude"));
                double longitude = Double.parseDouble(params.get("longitude"));
                int year = Integer.parseInt(params.get("year"));
                int month = Integer.parseInt(params.get("month"));
                int day = Integer.parseInt(params.get("day"));
                String gribFile = params.get("grib_file");
                
                try (Connection connection = connectToDatabase()) {
                    double maxTemperature = getMaxTemperature(connection, latitude, longitude, year, month, day, gribFile);
                    
                    String responseText = "Max Temperature: " + maxTemperature;
                    exchange.sendResponseHeaders(200, responseText.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } catch (Exception e) {
                    String responseText = "Error: " + e.getMessage();
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

        private double getMaxTemperature(Connection connection, double latitude, double longitude, int year, int month, int day, String gribFile) throws Exception {
            String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setInt(3, year);
                statement.setInt(4, month);
                statement.setInt(5, day);
                statement.setString(6, gribFile);

                ResultSet resultSet = statement.executeQuery();
                
                if (resultSet.next()) {
                    return resultSet.getDouble(1);
                } else {
                    throw new Exception("No temperature data found");
                }
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> params = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    params.put(entry[0], entry[1]);
                } else {
                    params.put(entry[0], "");
                }
            }
            return params;
        }

        private Connection connectToDatabase() throws Exception {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String username = "your_username";
            String password = "your_password";
            
            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection(url, username, password);
        }
    }
}


Note: Replace `your_database`, `your_username`, and `your_password` with your actual MySQL database name, username, and password. Ensure the necessary MySQL connector JAR is included in your classpath.