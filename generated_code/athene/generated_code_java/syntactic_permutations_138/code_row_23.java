import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Route;
import spark.Service;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Service httpService = Service.ignite();
        httpService.get("/check-moderator", checkModeratorRoute());
    }

    private static Route checkModeratorRoute() {
        return (request, response) -> {
            String username = request.queryParams("username");
            boolean isModerator = isUserModerator(username);
            return "{\"is_moderator\": " + isModerator + "}";
        };
    }

    private static boolean isUserModerator(String username) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        }
        return false;
    }
}