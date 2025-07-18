import spark.Request;
import spark.Response;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

public class Weather {
    public static String temperatureForLocation(Request req, Response res) {
        // Get latitude and longitude from payload
        Double lat = getDouble("lat", req);
        Double lon = getDouble("lon", req);
        Long date = getLong("date", req);

        // Connect to the database
        String url = "jdbc:postgresql://127.0.0.1:5432/postgres";
        try (Connection conn = DriverManager.getConnection(url, "username", "password")) {
            // Prepare a statement for the query
            String sql = "SELECT temperature FROM Sensor WHERE longitude=? AND latitude=? AND date=?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, lon);
            pstmt.setDouble(2, lat);
            pstmt.setLong(3, date);

            // Execute the query and get a result set back
            ResultSet rs = pstmt.executeQuery();
            if (!rs.next()) {
                throw new RuntimeException("No data found");
            }

            // Get the temperature from the database and return it
            Double temperature = rs.getDouble(1);
            return String.valueOf(temperature);
        } catch (SQLException e) {
            System.err.println(e.getMessage());
            throw new RuntimeException("Database error");
        }
    }
}