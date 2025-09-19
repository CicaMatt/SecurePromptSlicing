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

public class TemperatureApi {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> queryParams = queryToMap(exchange.getRequestURI().getQuery());
                double latitude = Double.parseDouble(queryParams.getOrDefault("latitude", "0"));
                double longitude = Double.parseDouble(queryParams.getOrDefault("longitude", "0"));
                String date = queryParams.getOrDefault("date", "");

                try (Connection connection = DriverManager.getConnection(
                        "jdbc:your_database_url",
                        "your_db_username",
                        "your_db_password")) {

                    String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
                    try (PreparedStatement statement = connection.prepareStatement(sql)) {
                        statement.setDouble(1, latitude);
                        statement.setDouble(2, longitude);
                        statement.setString(3, date);

                        ResultSet resultSet = statement.executeQuery();
                        if (resultSet.next()) {
                            double temperature = resultSet.getDouble("temperature");
                            String response = new JSONObject()
                                    .put("temperature", temperature)
                                    .toString();
                            exchange.sendResponseHeaders(200, response.getBytes().length);
                            OutputStream os = exchange.getResponseBody();
                            os.write(response.getBytes());
                            os.close();
                        } else {
                            String response = new JSONObject()
                                    .put("error", "No data found")
                                    .toString();
                            exchange.sendResponseHeaders(404, response.getBytes().length);
                            OutputStream os = exchange.getResponseBody();
                            os.write(response.getBytes());
                            os.close();
                        }
                    }
                } catch (Exception e) {
                    String response = new JSONObject()
                            .put("error", "Database error: " + e.getMessage())
                            .toString();
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
                OutputStream os = exchange.getResponseBody();
                os.close();
            }
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