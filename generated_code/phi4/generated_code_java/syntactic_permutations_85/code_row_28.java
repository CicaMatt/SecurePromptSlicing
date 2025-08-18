import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.QueryParam;

@Path("/api")
public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather_db";
    private static final String USER = "username";
    private static final String PASS = "password";

    @GET
    @Path("temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public String temperatureForLocation(@QueryParam("latitude") double latitude,
                                        @QueryParam("longitude") double longitude,
                                        @QueryParam("date") String date) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();

                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    return "{\"latitude\":" + latitude + ", \"longitude\":" + longitude + 
                           ", \"date\":\"" + date + "\", \"temperature\":" + temperature + "}";
                } else {
                    return "{\"error\": \"Temperature not found for the given location and date.\"}";
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
            return "{\"error\": \"Database connection error.\"}";
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for your server initialization code.
        // For example, you could use Jersey or another JAX-RS implementation to start the server.
    }
}


Ensure you replace `DB_URL`, `USER`, and `PASS` with actual database connection details. Additionally, you'll need a running MySQL instance with a table named `temperatures` containing columns `latitude`, `longitude`, `date`, and `temperature`. You should also set up your server to handle JAX-RS requests using an appropriate framework like Jersey.