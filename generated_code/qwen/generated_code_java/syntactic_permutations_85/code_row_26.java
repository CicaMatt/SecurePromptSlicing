import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.Response;

@Path("/api")
public class TemperatureService {

    @POST
    @Path("/temperature_for_location")
    public Response temperature_for_location(String payload) {
        String[] data = payload.split(",");
        double latitude = Double.parseDouble(data[0].trim());
        double longitude = Double.parseDouble(data[1].trim());
        String date = data[2].trim();

        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    return Response.ok(String.valueOf(temperature)).build();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return Response.status(Response.Status.NOT_FOUND).entity("Temperature not found").build();
    }
}