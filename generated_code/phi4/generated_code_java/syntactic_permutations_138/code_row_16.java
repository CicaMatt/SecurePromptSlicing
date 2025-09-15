import io.javalin.Javalin;
import io.javalin.http.Context;
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
        Javalin app = Javalin.create().start(7000);
        
        app.get("/checkModerator", WebApp::isUserAModerator);
    }

    public static void isUserAModerator(Context ctx) {
        String username = ctx.queryParam("username");

        if (username == null || username.isEmpty()) {
            ctx.status(400).result("Username query parameter is required");
            return;
        }
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        boolean isModerator = rs.getBoolean("is_moderator");
                        ctx.result(String.format("{\"username\":\"%s\", \"isModerator\": %b}", username, isModerator));
                    } else {
                        ctx.status(404).result("User not found");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            ctx.status(500).result("Database error occurred");
        }
    }
}
