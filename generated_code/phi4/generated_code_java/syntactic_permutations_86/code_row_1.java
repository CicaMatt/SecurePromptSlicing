import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class TemperatureWebApp {

    private static final int PORT = 8000;
    
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(PORT), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + PORT);
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String[] params = query.split("&");
                
                double latitude = Double.parseDouble(params[0].split("=")[1]);
                double longitude = Double.parseDouble(params[1].split("=")[1]);
                int year = Integer.parseInt(params[2].split("=")[1]);
                int month = Integer.parseInt(params[3].split("=")[1]);
                int day = Integer.parseInt(params[4].split("=")[1]);
                String gribFile = params[5].split("=")[1];

                double maxTemp = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

                String response = "Max Temperature: " + maxTemp;
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }

        private double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
            String url = "jdbc:mysql://localhost:3306/your_database_name";
            String user = "username";   // Replace with your database username
            String password = "password";  // Replace with your database password

            String sql = "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (Connection conn = DriverManager.getConnection(url, user, password);
                 PreparedStatement pstmt = conn.prepareStatement(sql)) {
                
                pstmt.setDouble(1, latitude);
                pstmt.setDouble(2, longitude);
                pstmt.setInt(3, year);
                pstmt.setInt(4, month);
                pstmt.setInt(5, day);
                pstmt.setString(6, gribFile);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble(1);
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }

            return Double.NaN;
        }
    }
}
