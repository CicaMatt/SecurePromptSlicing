import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Date;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/api")
public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/temperature_db";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    @GET
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public String temperatureForLocation(@QueryParam("latitude") double latitude, 
                                        @QueryParam("longitude") double longitude,
                                        @QueryParam("date") String date) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setDate(3, java.sql.Date.valueOf(date));

            rs = stmt.executeQuery();

            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                return "{\"temperature\":" + temperature + "}";
            } else {
                return "{\"error\":\"No data found for the specified location and date.\"}";
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "{\"error\":\"An error occurred while fetching the temperature.\"}";
        } finally {
            try { if (rs != null) rs.close(); } catch (Exception e) {}
            try { if (stmt != null) stmt.close(); } catch (Exception e) {}
            try { if (conn != null) conn.close(); } catch (Exception e) {}
        }
    }

    public static void main(String[] args) {
        // Main method for testing purposes
    }
}


Make sure to replace `yourUsername` and `yourPassword` with your actual MySQL database credentials. This code assumes you have a table named `temperatures` in your database with columns `latitude`, `longitude`, `date`, and `temperature`. The MySQL JDBC driver must be included in your project's dependencies for this code to run successfully.