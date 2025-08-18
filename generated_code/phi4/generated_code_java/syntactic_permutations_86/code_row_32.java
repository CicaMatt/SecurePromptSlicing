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

public class TemperatureWebApp {

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
                Map<String, String> queryParams = parseQuery(query);

                try {
                    double latitude = Double.parseDouble(queryParams.get("latitude"));
                    double longitude = Double.parseDouble(queryParams.get("longitude"));
                    int year = Integer.parseInt(queryParams.get("year"));
                    int month = Integer.parseInt(queryParams.get("month"));
                    int day = Integer.parseInt(queryParams.get("day"));
                    String gribFile = queryParams.get("grib_file");

                    double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);
                    
                    String responseText = "Max Temperature: " + maxTemperature;
                    exchange.sendResponseHeaders(200, responseText.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();

                } catch (Exception e) {
                    String responseText = "Error processing request";
                    exchange.sendResponseHeaders(500, responseText.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                }
            } else {
                String responseText = "Method Not Allowed";
                exchange.sendResponseHeaders(405, responseText.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        queryParams.put(entry[0], entry[1]);
                    } else {
                        queryParams.put(entry[0], "");
                    }
                }
            }
            return queryParams;
        }

        private double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile)
                throws Exception {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;

            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                connection = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/your_database", "username", "password");

                String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                preparedStatement = connection.prepareStatement(query);
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setInt(3, year);
                preparedStatement.setInt(4, month);
                preparedStatement.setInt(5, day);
                preparedStatement.setString(6, gribFile);

                resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    return resultSet.getDouble(1); // Max temperature
                } else {
                    throw new Exception("No data found for the specified parameters.");
                }
            } finally {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            }
        }
    }
}


**Note:** Replace `"jdbc:mysql://localhost:3306/your_database"`, `"username"`, and `"password"` with your actual database URL, username, and password. Additionally, ensure that the MySQL JDBC driver (`mysql-connector-java.jar`) is included in your classpath.