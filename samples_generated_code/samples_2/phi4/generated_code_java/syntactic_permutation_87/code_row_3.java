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

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/temperature_db";
    private static final String USER = "username";
    private static final String PASS = "password";

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
                String query = exchange.getRequestURI().getQuery();
                String[] params = query.split("&");
                
                double latitude = Double.parseDouble(params[0].split("=")[1]);
                double longitude = Double.parseDouble(params[1].split("=")[1]);
                String date = params[2].split("=")[1];

                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        stmt.setDouble(1, latitude);
                        stmt.setDouble(2, longitude);
                        stmt.setString(3, date);

                        try (ResultSet rs = stmt.executeQuery()) {
                            if (rs.next()) {
                                String temperature = rs.getString("temperature");
                                exchange.sendResponseHeaders(200, temperature.length());
                                OutputStream os = exchange.getResponseBody();
                                os.write(temperature.getBytes());
                                os.close();
                            } else {
                                String response = "Temperature not found";
                                exchange.sendResponseHeaders(404, response.length());
                                OutputStream os = exchange.getResponseBody();
                                os.write(response.getBytes());
                                os.close();
                            }
                        }
                    }
                } catch (Exception e) {
                    String response = "Internal server error: " + e.getMessage();
                    exchange.sendResponseHeaders(500, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method not allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}