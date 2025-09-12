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
public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    @GET
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public String temperatureForLocation(@QueryParam("latitude") double latitude, 
                                         @QueryParam("longitude") double longitude, 
                                         @QueryParam("date") String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                return "{\"temperature\":" + temperature + "}";
            } else {
                return "{\"error\":\"No data found for the given parameters.\"}";
            }
        } catch (ClassNotFoundException | SQLException e) {
            return "{\"error\":\"" + e.getMessage() + "\"}";
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        // Assuming you have a server setup to host this service
    }
}