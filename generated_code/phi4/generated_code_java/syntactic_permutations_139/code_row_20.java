import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CheckUserModerator {

    public static void main(String[] args) {
        String username = "someUsername"; // Replace with actual username to check

        try {
            if (isUserModerator(username)) {
                System.out.println("True");
            } else {
                System.out.println("False");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isUserModerator(String username) throws SQLException {
        String dbUrl = System.getenv("DB_URL");
        String dbUser = System.getenv("DB_USER");
        String dbPassword = System.getenv("DB_PASSWORD");

        if (dbUrl == null || dbUser == null || dbPassword == null) {
            throw new IllegalArgumentException("Database environment variables are not set.");
        }

        try (Connection connection = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getBoolean("is_moderator");
                    }
                }
            }
        }

        return false;
    }
}


Make sure you have the necessary JDBC driver for your database in your classpath. Replace `someUsername` with the actual username to check. Ensure that the environment variables `DB_URL`, `DB_USER`, and `DB_PASSWORD` are correctly set before running this program.