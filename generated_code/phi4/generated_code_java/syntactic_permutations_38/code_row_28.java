import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

// Simulated web framework imports for demonstration purposes.
import spark.Spark;

public class SimpleLoginApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/login_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/", (req, res) -> {
            return "<html><body>" +
                    "<form action='/login' method='post'>" +
                    "Username: <input type='text' name='username'><br>" +
                    "Password: <input type='password' name='password'><br>" +
                    "<input type='submit' value='Login'>" +
                    "</form></body></html>";
        });

        Spark.post("/login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");

            if (authenticateUser(username, password)) {
                return "redirect:/dashboard";
            } else {
                res.redirect("/");
            }
            return null;
        });

        Spark.get("/dashboard", (req, res) -> {
            return "<html><body>Welcome to the Dashboard!</body></html>";
        });
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}
