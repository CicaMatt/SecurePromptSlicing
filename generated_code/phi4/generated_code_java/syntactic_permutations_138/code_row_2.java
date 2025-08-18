import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import org.jetbrains.annotations.NotNull;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        ApiBuilder.get(app, "/checkModerator/:username", ctx -> {
            @NotNull String username = ctx.pathParam("username");
            boolean isModerator = checkIfUserIsModerator(username);
            ctx.result(isModerator ? "User is a moderator" : "User is not a moderator");
        });
    }

    private static boolean checkIfUserIsModerator(String username) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT role FROM users WHERE username = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        return "moderator".equalsIgnoreCase(rs.getString("role"));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project dependencies.