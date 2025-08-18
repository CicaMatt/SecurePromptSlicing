import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Response;

@Path("/api")
public class TemperatureService {

    @GET
    @Path("/temperature_for_location")
    public Response temperature_for_location(@QueryParam("date") String date, @QueryParam("location") String location) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT temperature FROM temperatures WHERE date = ? AND location = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, date);
                statement.setString(2, location);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double temperature = resultSet.getDouble("temperature");
                        return Response.ok(String.valueOf(temperature)).build();
                    } else {
                        return Response.status(Response.Status.NOT_FOUND).entity("Temperature not found").build();
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return Response.serverError().entity("Database error").build();
        }
    }
}