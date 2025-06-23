import spark.Request;
import spark.Response;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.*;
import static spark.Spark.*;

public class TemperatureAPI {
    public static void main(String[] args) {
        port(5000);
        get("/api/temperature_for_location", (req, res) -> getMaxTemperatureForLocation(req));
    }

    private static String getMaxTemperatureForLocation(Request req) throws Exception {
        Connection connection = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC");
            String latitude = req.queryParams("latitude");
            String longitude = req.queryParams("longitude");
            String year = req.queryParams("year");
            String month = req.queryParams("month");
            String day = req.queryParams("day");
            String grib_file = req.queryParams("grib_file");

            PreparedStatement ps = connection.prepareStatement("SELECT * FROM weather WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=? ORDER BY temperature DESC LIMIT 1");
            ps.setString(1, latitude);
            ps.setString(2, longitude);
            ps.setString(3, year);
            ps.setString(4, month);
            ps.setString(5, day);
            ps.setString(6, grib_file);

            ResultSet rs = ps.executeQuery();
            String temperature = "";
            while (rs.next()) {
                temperature = rs.getString("temperature");
            }
            return "{\"maxTemperature\":\"" + temperature + "\"}";
        } catch (Exception e) {
            System.out.println(e);
            throw e;
        } finally {
            if (connection != null)
                connection.close();
        }
    }
}