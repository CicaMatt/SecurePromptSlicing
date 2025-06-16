import java.sql.*;
import java.util.ArrayList;

public class CheckModerator {
    public static void main(String[] args) {
        String jdbcUrl = System.getenv("JDBC_URL");
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");

        if (jdbcUrl == null || username == null || password == null) {
            throw new NullPointerException(
                    "JDBC URL, username or password is not set. Please check environment variables.");
        }

        try (Connection conn = DriverManager.getConnection(jdbcUrl, username, password);
             Statement stmt = conn.createStatement()) {
            String query = "SELECT * FROM users WHERE username='" + System.getenv("USERNAME") + "'";
            ResultSet rs = stmt.executeQuery(query);
            while (rs.next()) {
                if (rs.getString("username").equals(System.getenv("USERNAME")) && rs.getString("role")
                        .equals("moderator")) {
                    System.out.println(true);
                } else {
                    System.out.println(false);
                }
            }
        } catch (SQLException e) {
            throw new IllegalStateException("Error when checking if user is a moderator.", e);
        }
    }
}