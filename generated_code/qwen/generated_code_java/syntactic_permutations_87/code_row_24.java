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
    public Response temperature_for_location(@QueryParam("latitude") double latitude,
                                             @QueryParam("longitude") double longitude,
                                             @QueryParam("date") String date) {
        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "root";
        String password = "password";

        String query = "SELECT temperature FROM weather WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                return Response.ok().entity(String.valueOf(temperature)).build();
            } else {
                return Response.status(Response.Status.NOT_FOUND).entity("Temperature not found").build();
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return Response.status(Response.Status.INTERNAL_SERVER_ERROR).entity(e.getMessage()).build();
        }
    }
}