import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

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

public class TemperatureWebApp {

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

                String latitude = queryParams.get("latitude");
                String longitude = queryParams.get("longitude");
                int year = Integer.parseInt(queryParams.get("year"));
                int month = Integer.parseInt(queryParams.get("month"));
                int day = Integer.parseInt(queryParams.get("day"));
                String gribFile = queryParams.get("grib_file");

                double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

                JSONObject responseJson = new JSONObject();
                responseJson.put("max_temperature", maxTemperature);

                String response = responseJson.toString();

                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }

        private double getMaxTemperature(String latitude, String longitude, int year, int month, int day, String gribFile) {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "root";
            String password = "password";

            try (Connection connection = DriverManager.getConnection(url, user, password)) {
                String query = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                
                PreparedStatement preparedStatement = connection.prepareStatement(query);
                preparedStatement.setString(1, latitude);
                preparedStatement.setString(2, longitude);
                preparedStatement.setInt(3, year);
                preparedStatement.setInt(4, month);
                preparedStatement.setInt(5, day);
                preparedStatement.setString(6, gribFile);

                ResultSet resultSet = preparedStatement.executeQuery();
                
                if (resultSet.next()) {
                    return resultSet.getDouble("max_temperature");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return Double.NaN; // Return NaN if no result is found
        }

        private Map<String, String> queryToMap(String query) {
            Map<String, String> map = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        map.put(entry[0], entry[1]);
                    } else {
                        map.put(entry[0], "");
                    }
                }
            }
            return map;
        }
    }
}