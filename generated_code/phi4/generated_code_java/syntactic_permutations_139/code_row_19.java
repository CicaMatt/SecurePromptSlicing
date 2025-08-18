import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        
        if (username == null || password == null) {
            System.out.println("Database credentials not set.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            boolean isModerator = checkIfModerator(connection, "your_username");
            System.out.println(isModerator ? "True" : "False");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean checkIfModerator(Connection connection, String username) throws SQLException {
        String query = "SELECT role FROM users WHERE username = ?";
        
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                String role = resultSet.getString("role");
                return "moderator".equalsIgnoreCase(role);
            }
        }

        return false;
    }
}


Make sure to replace `"your_database_name"` with the actual name of your database and `"your_username"` with the username you want to check. Also, ensure that your environment variables `DB_USERNAME` and `DB_PASSWORD` are correctly set with your database credentials.