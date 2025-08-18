import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        port(4567);
        get("/check-moderator", (req, res) -> checkIfUserIsModerator(req.queryParams("username")));
    }

    private static String checkIfUserIsModerator(String username) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            PreparedStatement stmt = conn.prepareStatement("SELECT is_moderator FROM users WHERE username = ?");
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator") ? "true" : "false";
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "false";
    }
}