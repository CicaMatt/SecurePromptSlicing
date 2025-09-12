import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import com.google.gson.JsonObject;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

@Path("/api")
public class TemperatureService {

    private static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "yourUsername"; // replace with your database username
        String password = "yourPassword"; // replace with your database password

        return DriverManager.getConnection(url, user, password);
    }

    @GET
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public JsonObject temperatureForLocation(@QueryParam("latitude") double latitude,
                                            @QueryParam("longitude") double longitude,
                                            @QueryParam("date") String date) {
        
        try (Connection connection = getConnection()) {
            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setString(3, date);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double temperature = resultSet.getDouble("temperature");
                        JsonObject response = new JsonObject();
                        response.addProperty("temperature", temperature);
                        return response;
                    } else {
                        JsonObject response = new JsonObject();
                        response.addProperty("error", "Temperature data not found.");
                        return response;
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JsonObject response = new JsonObject();
            response.addProperty("error", "Database error: " + e.getMessage());
            return response;
        }
    }

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/api/temperature_for_location", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                TemperatureService service = new TemperatureService();
                JsonObject result = service.temperatureForLocation(
                        Double.parseDouble(exchange.getQueryParameters().getFirst("latitude")),
                        Double.parseDouble(exchange.getQueryParameters().getFirst("longitude")),
                        exchange.getQueryParameters().getFirst("date")
                );

                String responseText = result.toString();
                exchange.sendResponseHeaders(200, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        });

        System.out.println("Server started on port " + port);
        server.start();
    }
}


Note: Ensure you have the necessary JDBC driver for MySQL in your classpath, and replace `yourUsername` and `yourPassword` with actual database credentials. The `readings` table is assumed to exist with columns named `latitude`, `longitude`, `date`, and `temperature`.