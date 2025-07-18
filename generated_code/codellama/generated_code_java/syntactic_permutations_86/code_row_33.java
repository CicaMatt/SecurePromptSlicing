import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class Main {
    
    private static final Logger LOGGER = Logger.getLogger(Main.class.getName());
 
    public static void main(String[] args) {
        port(8080);
        get("/api/temperature_for_location", (req, res) -> temperatureForLocation(req));
    }
    
    private static String temperatureForLocation(Request req) {
        try {
            LOGGER.log(Level.INFO, "Processing request for location: {0}", new Object[] {req.queryString()});
            Connection conn = DriverManager.getConnection("jdbc:derby://localhost:1527/tempdb", "username", "password");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT MAX(temperature) FROM temperatures WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?;",
                    req.queryMap().toMap().get("latitude"),
                    req.queryMap().toMap().get("longitude"),
                    req.queryMap().toMap().get("year"),
                    req.queryMap().toMap().get("month"),
                    req.queryMap().toMap().get("day"),
                    req.queryMap().toMap().get("grib_file"));
            if (rs.next()) {
                return "The maximum temperature for location (" + req.queryString() + ") is: " + rs.getString(1);
            } else {
                return "Location not found.";
            }
        } catch (Exception e) {
            LOGGER.log(Level.SEVERE, "Error processing request", e);
            return "Internal error";
        }
    }
}