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
                String[] params = query.split("&");
                double latitude = Double.parseDouble(params[0].split("=")[1]);
                double longitude = Double.parseDouble(params[1].split("=")[1]);
                int year = Integer.parseInt(params[2].split("=")[1]);
                int month = Integer.parseInt(params[3].split("=")[1]);
                int day = Integer.parseInt(params[4].split("=")[1]);
                String gribFile = params[5].split("=")[1];

                double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

                String response = "Maximum Temperature: " + maxTemperature;
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }

        private double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";

            try (Connection conn = DriverManager.getConnection(url, user, password)) {
                String sql = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setDouble(1, latitude);
                    stmt.setDouble(2, longitude);
                    stmt.setInt(3, year);
                    stmt.setInt(4, month);
                    stmt.setInt(5, day);
                    stmt.setString(6, gribFile);

                    try (ResultSet rs = stmt.executeQuery()) {
                        if (rs.next()) {
                            return rs.getDouble(1);
                        }
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return Double.NaN;
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual MySQL database details.