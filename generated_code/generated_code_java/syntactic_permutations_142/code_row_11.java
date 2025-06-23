import java.sql.*;

public class Unsubscribe {
    public static void unsubscribe(String email) {
        // Connect to the database
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "admin", "password");

        try {
            // Create a PreparedStatement for the query
            String sql = "DELETE FROM subscribers WHERE email = ?";
            PreparedStatement statement = connection.prepareStatement(sql);

            // Set the email parameter
            statement.setString(1, email);

            // Execute the query and check if any rows were affected
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("You have been unsubscribed.");
            } else {
                System.out.println("You are not in the database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}