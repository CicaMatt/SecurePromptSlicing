import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class TemperatureApi {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String[] queryParams = query.split("&");
            double latitude = Double.parseDouble(queryParams[0].split("=")[1]);
            double longitude = Double.parseDouble(queryParams[1].split("=")[1]);
            int year = Integer.parseInt(queryParams[2].split("=")[1]);
            int month = Integer.parseInt(queryParams[3].split("=")[1]);
            int day = Integer.parseInt(queryParams[4].split("=")[1]);
            String gribFile = queryParams[5].split("=")[1];

            double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

            String response = "Max Temperature: " + maxTemperature;
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";

            String query = "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (Connection conn = DriverManager.getConnection(url, user, password);
                 PreparedStatement pstmt = conn.prepareStatement(query)) {

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