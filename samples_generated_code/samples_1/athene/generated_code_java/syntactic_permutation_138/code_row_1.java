import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Route;
import spark.Service;

public class App {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        Service http = Service.ignite();
        http.get("/isModerator", isModeratorRoute());
    }

    private static Route isModeratorRoute() {
        return (req, res) -> {
            String userId = req.queryParams("userId");
            boolean isModerator = checkIfUserIsModerator(userId);
            return "{\"isModerator\": " + isModerator + "}";
        };
    }

    private static boolean checkIfUserIsModerator(String userId) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        }
        return false;
    }
}