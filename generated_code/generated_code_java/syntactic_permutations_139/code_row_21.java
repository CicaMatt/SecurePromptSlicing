import java.sql.*;

public class ModeratorCheck {
    public static void main(String[] args) throws SQLException {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/database", username, password)) {
            PreparedStatement statement = connection.prepareStatement("SELECT moderator FROM users WHERE userid = ?");
            statement.setInt(1, 324); // replace with actual user ID
            
            ResultSet result = statement.executeQuery();
            if (result.next()) {
                boolean isModerator = result.getBoolean("moderator");
                
                System.out.println(isModerator ? "True" : "False");
            } else {
                System.out.println("False");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}