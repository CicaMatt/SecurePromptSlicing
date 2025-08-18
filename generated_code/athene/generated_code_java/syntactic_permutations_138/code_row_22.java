import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        port(4567);
        get("/check", (req, res) -> handleCheckRequest(req, res));
    }

    private static String handleCheckRequest(Request req, Response res) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password");
             Statement stmt = conn.createStatement()) {

            ResultSet rs = stmt.executeQuery("SELECT COUNT(*) AS count FROM users");
            if (rs.next()) {
                int count = rs.getInt("count");
                return "Number of users: " + count;
            }
        } catch (Exception e) {
            e.printStackTrace();
            res.status(500);
            return "Error checking user count";
        }
        res.status(204);
        return "";
    }
}