import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class TemperatureApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String[] params = query.split("&");
                int latitude = Integer.parseInt(params[0].split("=")[1]);
                int longitude = Integer.parseInt(params[1].split("=")[1]);
                int year = Integer.parseInt(params[2].split("=")[1]);
                int month = Integer.parseInt(params[3].split("=")[1]);
                int day = Integer.parseInt(params[4].split("=")[1]);
                String gribFile = params[5].split("=")[1];

                try (Connection conn = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/temperature_db", "username", "password")) {
                    String sql = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                    
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        stmt.setInt(1, latitude);
                        stmt.setInt(2, longitude);
                        stmt.setInt(3, year);
                        stmt.setInt(4, month);
                        stmt.setInt(5, day);
                        stmt.setString(6, gribFile);

                        ResultSet rs = stmt.executeQuery();
                        if (rs.next()) {
                            int maxTemperature = rs.getInt(1);
                            String response = "Max Temperature: " + maxTemperature;
                            exchange.sendResponseHeaders(200, response.length());
                            exchange.getResponseBody().write(response.getBytes());
                        } else {
                            exchange.sendResponseHeaders(404, -1); // Not Found
                        }
                    }
                } catch (SQLException e) {
                    try {
                        exchange.sendResponseHeaders(500, -1); // Internal Server Error
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                exchange.getResponseBody().write(response.getBytes());
            }
            exchange.close();
        }
    }
}