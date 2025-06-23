import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import spark.Request;
import spark.Response;
import spark.Route;

public class Weather {
    static String temperature_for_location(Request req, Response res) {
        String latitude = req.queryParams("latitude");
        String longitude = req.queryParams("longitude");
        String date = req.queryParams("date");
        String connectionUrl = "jdbc:mysql://localhost/Weather";
        try (Connection conn = DriverManager.getConnection(connectionUrl, "root", "password");
                Statement stmt = conn.createStatement();) {
            ResultSet rs = stmt.executeQuery("SELECT temperature FROM Weather WHERE latitude='" + latitude + "' AND longitude='" + longitude + "' AND date='" + date + "';");
            int temperature = 0;
            while (rs.next()) {
                temperature = rs.getInt("temperature");
            }
            return String.valueOf(temperature);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return "";
    }
}