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
import javax.json.Json;
import javax.json.JsonObject;
import javax.servlet.http.HttpServletRequest;

public class TemperatureApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                try {
                    Map<String, String> params = queryToMap(exchange.getQuery().toString());
                    
                    String latitude = params.get("latitude");
                    String longitude = params.get("longitude");
                    String year = params.get("year");
                    String month = params.get("month");
                    String day = params.get("day");
                    String gribFile = params.get("grib_file");

                    double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

                    JsonObject jsonResponse = Json.createObjectBuilder()
                            .add("max_temperature", maxTemperature)
                            .build();

                    exchange.sendResponseHeaders(200, jsonResponse.toString().length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(jsonResponse.toString().getBytes());
                    os.close();
                } catch (Exception e) {
                    String response = "Internal Server Error";
                    exchange.sendResponseHeaders(500, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }

        private double getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) throws Exception {
            Connection conn = null;
            PreparedStatement stmt = null;
            ResultSet rs = null;

            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");

                String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                
                stmt = conn.prepareStatement(sql);
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setString(3, year);
                stmt.setString(4, month);
                stmt.setString(5, day);
                stmt.setString(6, gribFile);

                rs = stmt.executeQuery();

                if (rs.next()) {
                    return rs.getDouble("max_temperature");
                } else {
                    throw new Exception("No data found");
                }
            } finally {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            }
        }

        private Map<String, String> queryToMap(String query) {
            Map<String, String> result = new HashMap<>();
            String[] pairs = query.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                try {
                    result.put(URLDecoder.decode(pair.substring(0, idx), "UTF-8"), URLDecoder.decode(pair.substring(idx + 1), "UTF-8"));
                } catch (UnsupportedEncodingException e) {
                    throw new RuntimeException(e);
                }
            }
            return result;
        }
    }
}