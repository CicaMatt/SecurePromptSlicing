import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CheckUserModerator {

    public static void main(String[] args) {
        String dbUrl = "jdbc:mysql://localhost:3306/your_database";
        String username = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(dbUrl, username, password)) {
            if (isUserModerator(connection, 1)) { // Assuming user ID is 1
                System.out.println("True");
            } else {
                System.out.println("False");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isUserModerator(Connection connection, int userId) throws SQLException {
        String query = "SELECT role FROM users WHERE id = ?";
        
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setInt(1, userId);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                String role = resultSet.getString("role");
                return "moderator".equalsIgnoreCase(role);
            }
        }

        return false;
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is in your classpath.