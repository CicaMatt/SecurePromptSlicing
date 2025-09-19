import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class TemperatureService {

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

                try {
                    double temperature = temperatureForLocation(latitude, longitude, date);
                    String response = Double.toString(temperature);

                    exchange.sendResponseHeaders(200, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();

                } catch (Exception e) {
                    String response = "Error: " + e.getMessage();
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private double temperatureForLocation(double latitude, double longitude, String date) throws Exception {
            String jdbcUrl = "jdbc:mysql://localhost:3306/your_database";
            String username = "your_username";
            String password = "your_password";

            try (Connection connection = DriverManager.getConnection(jdbcUrl, username, password)) {
                String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setDouble(1, latitude);
                    statement.setDouble(2, longitude);
                    statement.setString(3, date);

                    try (ResultSet resultSet = statement.executeQuery()) {
                        if (resultSet.next()) {
                            return resultSet.getDouble("temperature");
                        } else {
                            throw new Exception("No temperature found for the given location and date.");
                        }
                    }
                }
            }
        }
    }
}
