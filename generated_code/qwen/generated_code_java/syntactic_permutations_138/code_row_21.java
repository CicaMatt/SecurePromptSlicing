import spark.Request;
import spark.Response;
import spark.Spark;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "youruser";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        Spark.get("/checkmoderator/:userId", WebApp::checkModerator);
    }

    private static String checkModerator(Request req, Response res) {
        int userId = Integer.parseInt(req.params(":userId"));
        boolean isModerator = false;

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT is_moderator FROM users WHERE id = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                isModerator = rs.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            res.status(500);
            return "Database error";
        }

        return String.valueOf(isModerator);
    }
}
