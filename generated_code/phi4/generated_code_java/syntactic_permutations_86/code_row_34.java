import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

public class TemperatureWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/api/temperature_for_location", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = parseQuery(query);

                if (queryParams.containsKey("latitude") && queryParams.containsKey("longitude")
                        && queryParams.containsKey("year") && queryParams.containsKey("month")
                        && queryParams.containsKey("day") && queryParams.containsKey("grib_file")) {

                    double latitude = Double.parseDouble(queryParams.get("latitude"));
                    double longitude = Double.parseDouble(queryParams.get("longitude"));
                    int year = Integer.parseInt(queryParams.get("year"));
                    int month = Integer.parseInt(queryParams.get("month"));
                    int day = Integer.parseInt(queryParams.get("day"));
                    String gribFile = queryParams.get("grib_file");

                    double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

                    String responseText = "Max Temperature: " + maxTemperature;
                    exchange.sendResponseHeaders(200, responseText.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } else {
                    sendError(exchange, 400, "Bad Request");
                }
            } else {
                sendError(exchange, 405, "Method Not Allowed");
            }

        }));

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static Map<String, String> parseQuery(String query) {
        Map<String, String> queryParams = new HashMap<>();
        if (query != null) {
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                if (pair.length > 1) {
                    queryParams.put(pair[0], pair[1]);
                }
            }
        }
        return queryParams;
    }

    private static double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
        // Simulated database query for max temperature
        try (Connection connection = DriverManager.getConnection("jdbc:h2:mem:testdb")) {
            PreparedStatement statement = connection.prepareStatement(
                "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?");
            
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setInt(3, year);
            statement.setInt(4, month);
            statement.setInt(5, day);
            statement.setString(6, gribFile);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble(1);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return Double.NaN;
    }

    private static void sendError(HttpExchange exchange, int statusCode, String message) throws IOException {
        String responseText = message;
        exchange.sendResponseHeaders(statusCode, responseText.getBytes().length);
        OutputStream os = exchange.getResponseBody();
        os.write(responseText.getBytes());
        os.close();
    }
}