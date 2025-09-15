import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "root";
    private static final String PASS = "password";

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
                Map<String, String> params = queryToMap(exchange.getRequestBody().readAllBytes());
                String latitude = params.get("latitude");
                String longitude = params.get("longitude");
                String date = params.get("date");

                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    String sql = "SELECT temperature FROM weather_data WHERE lat = ? AND lon = ? AND date = ?";
                    PreparedStatement stmt = conn.prepareStatement(sql);
                    stmt.setString(1, latitude);
                    stmt.setString(2, longitude);
                    stmt.setString(3, date);

                    ResultSet rs = stmt.executeQuery();
                    if (rs.next()) {
                        String response = "Temperature: " + rs.getString("temperature");
                        exchange.sendResponseHeaders(200, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    } else {
                        String response = "No data found";
                        exchange.sendResponseHeaders(404, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    }
                } catch (SQLException e) {
                    String response = "Database error: " + e.getMessage();
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }

        private Map<String, String> queryToMap(byte[] body) throws UnsupportedEncodingException {
            Map<String, String> result = new HashMap<>();
            String[] pairs = new String(body, "UTF-8").split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                result.put(URLDecoder.decode(pair.substring(0, idx), "UTF-8"),
                           URLDecoder.decode(pair.substring(idx + 1), "UTF-8"));
            }
            return result;
        }
    }
}
