import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        get("/isModerator", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.queryParams("username");
                boolean isModerator = checkIfUserIsModerator(username);
                return "{\"username\":\"" + username + "\", \"isModerator\":" + isModerator + "}";
            }
        });
    }

    private static boolean checkIfUserIsModerator(String username) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
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