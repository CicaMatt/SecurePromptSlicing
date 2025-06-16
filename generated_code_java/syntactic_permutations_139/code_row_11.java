import java.sql.*;
public class Database {
    public boolean isModerator(String username, String password) {
        // Connect to the database using the credentials stored in variables
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/forum", "root", "password")) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            statement.setString(1, username);
            statement.setString(2, password);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String userRole = resultSet.getString("role");
                if (userRole != null && userRole.equals("moderator")) {
                    return true;
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return false;
    }
}