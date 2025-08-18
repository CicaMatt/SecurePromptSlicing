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

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String[] params = query.split("&");
                String longitude = null, year = null, month = null, day = null, gribFile = null;

                for (String param : params) {
                    String[] keyValue = param.split("=");
                    if ("longitude".equals(keyValue[0])) {
                        longitude = keyValue[1];
                    } else if ("year".equals(keyValue[0])) {
                        year = keyValue[1];
                    } else if ("month".equals(keyValue[0])) {
                        month = keyValue[1];
                    } else if ("day".equals(keyValue[0])) {
                        day = keyValue[1];
                    } else if ("grib_file".equals(keyValue[0])) {
                        gribFile = keyValue[1];
                    }
                }

                if (longitude != null && year != null && month != null && day != null && gribFile != null) {
                    try (Connection conn = DriverManager.getConnection(
                            "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

                        String sql = "SELECT MAX(temperature) FROM temperatures WHERE longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
                        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                            stmt.setString(1, longitude);
                            stmt.setInt(2, Integer.parseInt(year));
                            stmt.setInt(3, Integer.parseInt(month));
                            stmt.setInt(4, Integer.parseInt(day));
                            stmt.setString(5, gribFile);

                            ResultSet rs = stmt.executeQuery();
                            if (rs.next()) {
                                String maxTemperature = rs.getString(1);
                                String response = "Max Temperature: " + maxTemperature;
                                exchange.sendResponseHeaders(200, response.getBytes().length);
                                exchange.getResponseBody().write(response.getBytes());
                            } else {
                                String response = "No data found";
                                exchange.sendResponseHeaders(404, response.getBytes().length);
                                exchange.getResponseBody().write(response.getBytes());
                            }
                        }
                    } catch (SQLException e) {
                        String response = "Database error: " + e.getMessage();
                        exchange.sendResponseHeaders(500, response.getBytes().length);
                        exchange.getResponseBody().write(response.getBytes());
                    }
                } else {
                    String response = "Invalid parameters";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    exchange.getResponseBody().write(response.getBytes());
                }
            } else {
                String response = "Method not allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                exchange.getResponseBody().write(response.getBytes());
            }

            exchange.close();
        }
    }
}