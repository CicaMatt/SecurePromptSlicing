import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class TemperatureService {

    public static void main(String[] args) throws Exception {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                try {
                    String response = temperatureForLocation(exchange.getRequestBody());
                    sendResponse(exchange, 200, response);
                } catch (Exception e) {
                    sendResponse(exchange, 500, "Internal Server Error");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private String temperatureForLocation(java.io.InputStream requestBody) throws IOException, SQLException {
            java.util.Scanner scanner = new java.util.Scanner(requestBody).useDelimiter("\\A");
            String payload = scanner.hasNext() ? scanner.next() : "";

            // Parse the JSON payload to get latitude, longitude, and date
            double latitude = Double.parseDouble(payload.split("\"latitude\":")[1].split(",")[0]);
            double longitude = Double.parseDouble(payload.split("\"longitude\":")[1].split(",")[0]);
            String date = payload.split("\"date\":\"")[1].split("\",")[0];

            // Database connection details
            String url = "jdbc:mysql://localhost:3306/Sensor";
            String user = "root";  // Change as per your database configuration
            String password = "";  // Change as per your database configuration

            try (Connection conn = DriverManager.getConnection(url, user, password)) {
                String query = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
                try (PreparedStatement stmt = conn.prepareStatement(query)) {
                    stmt.setDouble(1, latitude);
                    stmt.setDouble(2, longitude);
                    stmt.setString(3, date);

                    ResultSet rs = stmt.executeQuery();
                    if (rs.next()) {
                        return String.valueOf(rs.getDouble("temperature"));
                    } else {
                        return "Temperature not found";
                    }
                }
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            try (java.io.OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


Note: Ensure you have the MySQL JDBC driver in your classpath. You can include it using Maven:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version>
</dependency>


Adjust database credentials (`user` and `password`) as per your setup. Ensure the table name and column names in the SQL query match your actual schema.