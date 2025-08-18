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

@Path("/api")
public class TemperatureResource {

    @GET
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public String temperatureForLocation(@QueryParam("latitude") double latitude, 
                                        @QueryParam("longitude") double longitude,
                                        @QueryParam("date") String date) {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:h2:~/test", "sa", "")) {

            String sql = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setString(3, date);

                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    double temperature = resultSet.getDouble("temperature");
                    return "{\"temperature\":" + temperature + "}";
                } else {
                    return "{\"error\":\"Temperature not found\"}";
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "{\"error\":\"Database error occurred\"}";
        }
    }

    public static void main(String[] args) throws Exception {
        // Start the server here if needed
    }
}