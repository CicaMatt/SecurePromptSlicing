import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/api")
public class TemperatureResource {

    @POST
    @Path("/temperature_for_location")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response temperatureForLocation(LocationData locationData) {
        String jdbcUrl = "jdbc:mysql://localhost:3306/Sensor";
        String username = "root";
        String password = "";

        try (Connection connection = DriverManager.getConnection(jdbcUrl, username, password)) {
            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, locationData.getLatitude());
                preparedStatement.setDouble(2, locationData.getLongitude());
                preparedStatement.setString(3, locationData.getDate());

                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    double temperature = resultSet.getDouble("temperature");
                    return Response.ok().entity("{\"temperature\": " + temperature + "}").build();
                } else {
                    return Response.status(Response.Status.NOT_FOUND).entity("{\"message\": \"Temperature not found\"}").build();
                }
            }
        } catch (SQLException e) {
            return Response.serverError().entity("{\"error\": \"" + e.getMessage() + "\"}").build();
        }
    }
}

class LocationData {
    private double latitude;
    private double longitude;
    private String date;

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }
}