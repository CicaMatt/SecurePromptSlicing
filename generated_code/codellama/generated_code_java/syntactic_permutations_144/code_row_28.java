import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Unsubscribe {
    public static void main(String[] args) {
        String email = "user@example.com";
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname", "username", "password");
                PreparedStatement statement = conn.prepareStatement("SELECT 1 FROM users WHERE email=?")) {
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                // email exists in database
                unsubscribeEmail(email);
            } else {
                System.out.println("0");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    
    private static void unsubscribeEmail(String email) throws SQLException {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname", "username", "password");
                PreparedStatement statement = conn.prepareStatement("UPDATE users SET status=? WHERE email=?")) {
            statement.setInt(1, 0); // status of unsubscribed
            statement.setString(2, email);
            int result = statement.executeUpdate();
            if (result > 0) {
                System.out.println("1");
            } else {
                System.out.println("0");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}