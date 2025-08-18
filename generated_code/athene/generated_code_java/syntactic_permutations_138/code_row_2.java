import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Route;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/check-moderator", new Route() {
            @Override
            public Object handle(Object request) {
                String username = Spark.request().queryMap("username").value();
                return checkIfModerator(username);
            }
        });
    }

    private static Boolean checkIfModerator(String username) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password")) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getBoolean("is_moderator");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}