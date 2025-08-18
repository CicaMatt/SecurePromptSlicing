import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Route;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/checkUser", new Route() {
            @Override
            public Object handle(Object request) {
                String username = Spark.request().queryParam("username");
                return checkUser(username);
            }
        });
    }

    private static String checkUser(String username) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password")) {
            String query = "SELECT COUNT(*) FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, username);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        return "User found";
                    } else {
                        return "User not found";
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "Error checking user";
        }
    }
}