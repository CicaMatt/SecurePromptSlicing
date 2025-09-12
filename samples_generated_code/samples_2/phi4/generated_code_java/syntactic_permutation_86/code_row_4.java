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

public class TemperatureApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements com.sun.net.httpserver.HttpHandler {
        @Override
        public void handle(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> parameters = queryToMap(exchange.getRequestURI().getQuery());
                
                try (Connection connection = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/your_database", "username", "password")) {
                    
                    String lat = parameters.get("latitude");
                    String lon = parameters.get("longitude");
                    String year = parameters.get("year");
                    String month = parameters.get("month");
                    String day = parameters.get("day");
                    String gribFile = parameters.get("grib_file");

                    String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                    
                    try (PreparedStatement statement = connection.prepareStatement(query)) {
                        statement.setString(1, lat);
                        statement.setString(2, lon);
                        statement.setString(3, year);
                        statement.setString(4, month);
                        statement.setString(5, day);
                        statement.setString(6, gribFile);

                        ResultSet resultSet = statement.executeQuery();
                        
                        if (resultSet.next()) {
                            String maxTemp = resultSet.getString(1);
                            byte[] responseBytes = ("Maximum Temperature: " + maxTemp).getBytes();

                            exchange.sendResponseHeaders(200, responseBytes.length);
                            OutputStream os = exchange.getResponseBody();
                            os.write(responseBytes);
                            os.close();
                        } else {
                            exchange.sendResponseHeaders(404, -1);
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    exchange.sendResponseHeaders(500, -1);
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private Map<String, String> queryToMap(String query) {
            Map<String, String> result = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        result.put(entry[0], entry[1]);
                    }
                }
            }
            return result;
        }
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"username"`, and `"password"` with your actual database URL, username, and password. Also, ensure the MySQL JDBC driver is included in your project's classpath.