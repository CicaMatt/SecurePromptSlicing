import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        get("/isModerator", (req, res) -> handleIsModerator(req));
    }

    private static String handleIsModerator(Request req) {
        String username = req.queryParams("username");
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            PreparedStatement stmt = conn.prepareStatement("SELECT is_moderator FROM users WHERE username = ?");
            stmt.setString(1, username);
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