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

public class TemperatureApi {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response;
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> queryParams = queryToMap(exchange.getRequestURI().getQuery());
                double latitude = Double.parseDouble(queryParams.get("latitude"));
                double longitude = Double.parseDouble(queryParams.get("longitude"));
                java.sql.Date date = java.sql.Date.valueOf(queryParams.get("date"));

                try (Connection connection = getConnection()) {
                    response = getTemperatureForLocation(connection, latitude, longitude, date);
                } catch (Exception e) {
                    response = "Internal Server Error";
                }
            } else {
                response = "Method Not Allowed";
            }

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private String getTemperatureForLocation(Connection connection, double latitude, double longitude, java.sql.Date date) throws Exception {
            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setDate(3, date);

                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    return String.valueOf(resultSet.getDouble("temperature"));
                } else {
                    return "No temperature data found";
                }
            }
        }

        private Map<String, String> queryToMap(String query) {
            Map<String, String> result = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                }
            }
            return result;
        }
    }

    private static Connection getConnection() throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(url, user, password);
    }
}