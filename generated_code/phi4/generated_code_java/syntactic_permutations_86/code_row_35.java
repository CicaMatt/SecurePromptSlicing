import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
import javax.sql.DataSource;
import org.h2.jdbcx.JdbcDataSource;

public class TemperatureApi {

    private static final String DB_URL = "jdbc:h2:~/test";
    
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        JdbcDataSource ds = new JdbcDataSource();
        ds.setURL(DB_URL);
        DataSource dataSource = ds;

        server.createContext("/api/temperature_for_location", new TemperatureHandler(dataSource));
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        private final DataSource dataSource;

        public TemperatureHandler(DataSource dataSource) {
            this.dataSource = dataSource;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String queryParameters = exchange.getRequestURI().getQuery();

            Map<String, String> params = new HashMap<>();
            for (String param : queryParameters.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }

            String latitude = params.getOrDefault("latitude", "");
            String longitude = params.getOrDefault("longitude", "");
            String year = params.getOrDefault("year", "");
            String month = params.getOrDefault("month", "");
            String day = params.getOrDefault("day", "");
            String gribFile = params.getOrDefault("grib_file", "");

            if (latitude.isEmpty() || longitude.isEmpty() || year.isEmpty() || month.isEmpty() ||
                day.isEmpty() || gribFile.isEmpty()) {
                sendResponse(exchange, 400, "Missing parameters");
                return;
            }

            try (java.sql.Connection connection = dataSource.getConnection();
                 java.sql.PreparedStatement stmt = connection.prepareStatement(
                         "SELECT MAX(temperature) FROM temperature_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?")) {

                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setInt(3, Integer.parseInt(year));
                stmt.setInt(4, Integer.parseInt(month));
                stmt.setInt(5, Integer.parseInt(day));
                stmt.setString(6, gribFile);

                java.sql.ResultSet rs = stmt.executeQuery();

                if (rs.next()) {
                    int maxTemperature = rs.getInt(1);
                    sendResponse(exchange, 200, "Max Temperature: " + maxTemperature);
                } else {
                    sendResponse(exchange, 404, "No data found");
                }
            } catch (Exception e) {
                sendResponse(exchange, 500, "Internal Server Error");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes(StandardCharsets.UTF_8));
            os.close();
        }
    }
}