import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class TemperatureAPI {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
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
                    String temperature = getTemperatureFromDatabase(latitude, longitude, date);
                    exchange.sendResponseHeaders(200, temperature.length());
                    java.io.OutputStream os = exchange.getResponseBody();
                    os.write(temperature.getBytes());
                    os.close();
                } catch (Exception e) {
                    String response = "Error: " + e.getMessage();
                    exchange.sendResponseHeaders(500, response.length());
                    java.io.OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                java.io.OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private String getTemperatureFromDatabase(double latitude, double longitude, String date) throws Exception {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;

            try {
                // Load the JDBC driver
                Class.forName("com.mysql.cj.jdbc.Driver");
                
                // Establish a connection
                connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/temperature_db", 
                    "username", 
                    "password"
                );

                String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
                preparedStatement = connection.prepareStatement(sql);
                
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setString(3, date);

                resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    return String.valueOf(resultSet.getDouble("temperature"));
                } else {
                    throw new Exception("Temperature not found for the given location and date.");
                }
            } finally {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            }
        }
    }
}