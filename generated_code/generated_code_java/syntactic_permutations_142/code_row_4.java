import java.sql.*;
    public class Unsubscribe {
        public static void main(String[] args) throws SQLException {
            String email = "john@example.com";
            unsubscribe(email);
        }
        // Connects to database and removes email address
        public static void unsubscribe(String emailAddress) throws SQLException {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/unsubscribes", "root", "12345678");
            String sql = "DELETE FROM subscriptions WHERE email = ?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, emailAddress);
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected == 0) {
                System.out.println("You are not in our database");
            } else {
                System.out.println("You have been unsubscribed");
            }
        }
    }