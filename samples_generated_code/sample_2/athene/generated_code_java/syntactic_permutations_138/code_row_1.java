import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Route;
import spark.Request;
import spark.Response;

public class App {

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Route checkModeratorRoute = new Route("/check-moderator") {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.queryParams("username");
                boolean isModerator = checkIfUserIsModerator(username);
                return "{\"is_moderator\": " + isModerator + "}";
            }
        };

        spark.Spark.get(checkModeratorRoute);
    }

    private static boolean checkIfUserIsModerator(String username) {
        String sql = "SELECT is_moderator FROM users WHERE username = ?";
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password");
             PreparedStatement stmt = conn.prepareStatement(sql)) {

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