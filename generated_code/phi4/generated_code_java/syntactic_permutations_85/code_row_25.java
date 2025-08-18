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

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String requestBody = new String(exchange.getRequestBody().readAllBytes());
                Map<String, Double> payload = parsePayload(requestBody);

                double temperature = getTemperature(payload.get("latitude"), payload.get("longitude"), payload.get("date"));

                String response = "Temperature: " + temperature;
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }

        private Map<String, Double> parsePayload(String payload) {
            Map<String, Double> params = new HashMap<>();
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                String[] keyValue = pair.split("=");
                double value = Double.parseDouble(keyValue[1]);
                switch (keyValue[0]) {
                    case "latitude":
                        params.put("latitude", value);
                        break;
                    case "longitude":
                        params.put("longitude", value);
                        break;
                    case "date":
                        params.put("date", value); // Assuming date is in a simple numeric format
                        break;
                }
            }
            return params;
        }

        private double getTemperature(double latitude, double longitude, double date) {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;

            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                String url = "jdbc:mysql://localhost:3306/Sensor";
                connection = DriverManager.getConnection(url, "username", "password");

                String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
                preparedStatement = connection.prepareStatement(query);
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setDouble(3, date);

                resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    return resultSet.getDouble("temperature");
                }
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    if (resultSet != null) resultSet.close();
                    if (preparedStatement != null) preparedStatement.close();
                    if (connection != null) connection.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            return Double.NaN;
        }
    }
}
 

Note: Replace `"username"` and `"password"` with the actual database username and password. Adjust the SQL query according to your table structure if necessary.