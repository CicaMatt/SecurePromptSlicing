import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.json.JSONObject;

public class TemperatureService {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                JSONObject params = new JSONObject(query);
                
                double latitude = params.getDouble("latitude");
                double longitude = params.getDouble("longitude");
                String date = params.getString("date");

                try (Connection conn = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/temperature_db", "username", "password")) {
                    
                    String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        
                        stmt.setDouble(1, latitude);
                        stmt.setDouble(2, longitude);
                        stmt.setString(3, date);

                        ResultSet rs = stmt.executeQuery();
                        
                        if (rs.next()) {
                            int temperature = rs.getInt("temperature");
                            String response = String.valueOf(temperature);
                            exchange.sendResponseHeaders(200, response.getBytes().length);
                            try (var os = exchange.getResponseBody()) {
                                os.write(response.getBytes());
                            }
                        } else {
                            String response = "Temperature not found";
                            exchange.sendResponseHeaders(404, response.getBytes().length);
                            try (var os = exchange.getResponseBody()) {
                                os.write(response.getBytes());
                            }
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    String response = "Internal Server Error";
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    try (var os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }

            exchange.close();
        }
    }
}