import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.InetSocketAddress;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourDatabaseUser";
    private static final String PASS = "yourDatabasePassword";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String requestBody = new String(exchange.getRequestBody().readAllBytes());
                Map<String, String> payload = parsePayload(requestBody);

                double latitude = Double.parseDouble(payload.get("latitude"));
                double longitude = Double.parseDouble(payload.get("longitude"));
                String date = payload.get("date");

                double temperature = getTemperatureFromDatabase(latitude, longitude, date);
                
                String response = String.valueOf(temperature);
                
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private double getTemperatureFromDatabase(double latitude, double longitude, String date) {
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setDouble(1, latitude);
                    stmt.setDouble(2, longitude);
                    stmt.setString(3, date);

                    ResultSet rs = stmt.executeQuery();
                    if (rs.next()) {
                        return rs.getDouble("temperature");
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return Double.NaN;
        }

        private Map<String, String> parsePayload(String payload) {
            Map<String, String> params = new HashMap<>();
            try {
                java.util.Scanner scanner = new java.util.Scanner(new StringReader(payload));
                while (scanner.hasNext()) {
                    String[] keyValue = scanner.next().split("=");
                    if (keyValue.length == 2) {
                        params.put(keyValue[0], keyValue[1]);
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return params;
        }
    }
}
