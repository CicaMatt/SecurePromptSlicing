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
                String userId = Spark.request().queryParam("userId");
                return isUserModerator(userId);
            }
        });
    }

    private static boolean isUserModerator(String userId) {
        final String url = "jdbc:mysql://localhost:3306/mydb";
        final String user = "dbuser";
        final String password = "dbpassword";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, userId);
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