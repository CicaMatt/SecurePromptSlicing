import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import org.json.JSONObject;

public class TemperatureService {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "username"; // Replace with actual username
    private static final String PASS = "password"; // Replace with actual password

    public static void main(String[] args) throws IOException {
        int serverPort = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(serverPort), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String requestBody = new String(exchange.getRequestBody().readAllBytes());
                JSONObject jsonRequest = new JSONObject(requestBody);

                double latitude = jsonRequest.getDouble("latitude");
                double longitude = jsonRequest.getDouble("longitude");
                String date = jsonRequest.getString("date");

                try {
                    Double temperature = getTemperature(latitude, longitude, date);
                    if (temperature != null) {
                        String response = "Temperature: " + temperature;
                        sendResponse(exchange, 200, response);
                    } else {
                        sendResponse(exchange, 404, "Temperature data not found.");
                    }
                } catch (Exception e) {
                    sendResponse(exchange, 500, "Internal server error: " + e.getMessage());
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Double getTemperature(double latitude, double longitude, String date) throws SQLException {
            String query = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
                 PreparedStatement pstmt = conn.prepareStatement(query)) {

                pstmt.setDouble(1, latitude);
                pstmt.setDouble(2, longitude);
                pstmt.setString(3, date);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble("temperature");
                    }
                }
            }
            return null;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
