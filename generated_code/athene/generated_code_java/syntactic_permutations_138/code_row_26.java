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
        get("/isModerator", (req, res) -> isUserModerator(req.queryParams("userId")));
    }

    private static String isUserModerator(String userId) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            PreparedStatement stmt = conn.prepareStatement("SELECT is_moderator FROM users WHERE id = ?");
            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return Boolean.toString(rs.getBoolean("is_moderator"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "false";
    }
}