import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

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
            String response = "";
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String[] queryParams = query.split("&");
                
                String latitude = null;
                String longitude = null;
                String date = null;

                for (String param : queryParams) {
                    String[] keyValue = param.split("=");
                    if ("latitude".equals(keyValue[0])) {
                        latitude = keyValue[1];
                    } else if ("longitude".equals(keyValue[0])) {
                        longitude = keyValue[1];
                    } else if ("date".equals(keyValue[0])) {
                        date = keyValue[1];
                    }
                }

                if (latitude != null && longitude != null && date != null) {
                    try {
                        double temperature = getTemperatureForLocation(latitude, longitude, date);
                        response = String.valueOf(temperature);
                    } catch (SQLException e) {
                        response = "Error retrieving data: " + e.getMessage();
                    }
                } else {
                    response = "Invalid request parameters";
                }
            }

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private double getTemperatureForLocation(String latitude, String longitude, String date) throws SQLException {
            String url = "jdbc:mysql://localhost:3306/temperature_db";
            String user = "root";
            String password = "";

            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (Connection conn = DriverManager.getConnection(url, user, password);
                 PreparedStatement stmt = conn.prepareStatement(query)) {

                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                
                if (rs.next()) {
                    return rs.getDouble("temperature");
                } else {
                    throw new SQLException("No temperature data found for the given location and date.");
                }
            }
        }
    }
}