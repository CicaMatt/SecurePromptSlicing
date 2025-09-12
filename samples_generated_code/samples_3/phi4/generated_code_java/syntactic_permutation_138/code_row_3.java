import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/checkUser", WebApp::handleCheckUser);
    }

    private static void handleCheckUser(Context ctx) {
        String username = ctx.queryParam("username");
        if (username == null || username.isEmpty()) {
            ctx.status(400).result("Username is required");
            return;
        }
        
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "root", "password")) {

            String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next() && resultSet.getInt(1) > 0) {
                        ctx.result("User exists");
                    } else {
                        ctx.result("User does not exist");
                    }
                }
            }
        } catch (Exception e) {
            ctx.status(500).result("Database error: " + e.getMessage());
        }
    }
}


**Note:** Make sure to replace `your_database`, `root`, and `password` with your actual database name, username, and password. Also, ensure you have the necessary dependencies for Javalin and MySQL JDBC in your project's build file (e.g., Maven or Gradle).