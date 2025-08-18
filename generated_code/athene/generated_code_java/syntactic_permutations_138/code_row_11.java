import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/check-moderator", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String userId = request.queryParams("userId");
                return isUserModerator(userId);
            }
        });
    }

    private static Boolean isUserModerator(String userId) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password")) {
            PreparedStatement stmt = conn.prepareStatement("SELECT is_moderator FROM users WHERE id = ?");
            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}