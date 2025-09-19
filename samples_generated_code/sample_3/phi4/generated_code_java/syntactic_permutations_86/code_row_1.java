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
import java.util.Scanner;

public class WebApp {

    private static Connection connectToDatabase() throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        
        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(url, user, password);
    }

    public static class RequestHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (!"GET".equals(exchange.getRequestMethod())) {
                sendResponse(exchange, 405, "Method Not Allowed");
                return;
            }

            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = parseQuery(query);

            if (queryParams == null || !queryParams.containsKey("latitude") ||
                    !queryParams.containsKey("longitude") ||
                    !queryParams.containsKey("year") ||
                    !queryParams.containsKey("month") ||
                    !queryParams.containsKey("day") ||
                    !queryParams.containsKey("grib_file")) {
                sendResponse(exchange, 400, "Bad Request");
                return;
            }

            String latitude = queryParams.get("latitude");
            String longitude = queryParams.get("longitude");
            String year = queryParams.get("year");
            String month = queryParams.get("month");
            String day = queryParams.get("day");
            String gribFile = queryParams.get("grib_file");

            try (Connection conn = connectToDatabase()) {
                String sql = "SELECT MAX(temperature) FROM weather_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                try (PreparedStatement statement = conn.prepareStatement(sql)) {
                    statement.setString(1, latitude);
                    statement.setString(2, longitude);
                    statement.setInt(3, Integer.parseInt(year));
                    statement.setInt(4, Integer.parseInt(month));
                    statement.setInt(5, Integer.parseInt(day));
                    statement.setString(6, gribFile);

                    try (ResultSet resultSet = statement.executeQuery()) {
                        if (resultSet.next()) {
                            String maxTemp = resultSet.getString(1);
                            sendResponse(exchange, 200, "Max Temperature: " + maxTemp);
                        } else {
                            sendResponse(exchange, 404, "No Data Found");
                        }
                    }
                }
            } catch (Exception e) {
                sendResponse(exchange, 500, "Internal Server Error");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) return null;
            
            Map<String, String> queryParams = new HashMap<>();
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                if (pair.length == 2) {
                    queryParams.put(pair[0], pair[1]);
                }
            }
            return queryParams;
        }
    }

    public static void main(String[] args) throws Exception {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/api", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }
}