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

public class TemperatureWebApp {

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
                int year = Integer.parseInt(params[2].split("=")[1]);
                int day = Integer.parseInt(params[3].split("=")[1]);
                String gribFile = params[4].split("=")[1];
                
                try (Connection connection = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/your_database", "username", "password")) {
                    
                    String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data "
                                + "WHERE latitude = ? AND longitude = ? AND year = ? AND day = ? AND grib_file = ?";
                    
                    try (PreparedStatement statement = connection.prepareStatement(sql)) {
                        statement.setDouble(1, latitude);
                        statement.setDouble(2, longitude);
                        statement.setInt(3, year);
                        statement.setInt(4, day);
                        statement.setString(5, gribFile);
                        
                        ResultSet resultSet = statement.executeQuery();
                        
                        if (resultSet.next()) {
                            double maxTemperature = resultSet.getDouble("max_temperature");
                            String response = "Max Temperature: " + maxTemperature;
                            
                            exchange.sendResponseHeaders(200, response.getBytes().length);
                            OutputStream os = exchange.getResponseBody();
                            os.write(response.getBytes());
                            os.close();
                        } else {
                            String response = "No data found.";
                            
                            exchange.sendResponseHeaders(404, response.getBytes().length);
                            OutputStream os = exchange.getResponseBody();
                            os.write(response.getBytes());
                            os.close();
                        }
                    }
                } catch (Exception e) {
                    String response = "Internal server error: " + e.getMessage();
                    
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }
            } else {
                String response = "Method Not Allowed";
                
                exchange.sendResponseHeaders(405, response.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}


Before running the code, ensure you replace `your_database`, `username`, and `password` with your actual MySQL database name, username, and password. Also, make sure that the MySQL JDBC driver is available in the classpath. You might need to download it separately if not already included in your environment.