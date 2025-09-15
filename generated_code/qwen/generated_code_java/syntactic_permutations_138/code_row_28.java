import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public static void main(String[] args) {
        Spark.get("/checkmoderator/:userId", WebApp::isModerator);
    }

    private static String isModerator(Request req, Response res) {
        int userId = Integer.parseInt(req.params(":userId"));
        boolean isMod = checkIfUserIsModerator(userId);
        return "{\"isModerator\": " + isMod + "}";
    }

    private static boolean checkIfUserIsModerator(int userId) {
        String query = "SELECT is_moderator FROM users WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}
