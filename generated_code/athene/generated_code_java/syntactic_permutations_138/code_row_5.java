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
        Route isModeratorRoute = new Route("/is-moderator") {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String userId = request.queryParams("user_id");
                return checkIfUserIsModerator(userId);
            }
        };

        // Register the route (assuming you have a Spark Java server setup)
        spark.Spark.get(isModeratorRoute);
    }

    private static boolean checkIfUserIsModerator(String userId) {
        String sql = "SELECT is_moderator FROM users WHERE id = ?";
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password");
             PreparedStatement stmt = connection.prepareStatement(sql)) {

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