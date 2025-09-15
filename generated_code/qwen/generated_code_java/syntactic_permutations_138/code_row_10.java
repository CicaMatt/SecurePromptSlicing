import spark.Request;
import spark.Response;
import spark.Spark;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Spark.get("/checkModerator/:userId", WebApp::checkIfUserIsModerator);
    }

    private static String checkIfUserIsModerator(Request request, Response response) {
        String userId = request.params(":userId");
        boolean isModerator = false;

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, userId);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        isModerator = rs.getBoolean("is_moderator");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            response.status(500);
            return "Database error";
        }

        return String.valueOf(isModerator);
    }
}
