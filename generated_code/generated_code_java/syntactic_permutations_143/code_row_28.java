import java.sql.*;
import javax.naming.Context;
import javax.naming.InitialContext;

public class UnsubscribeService {
    public void unsubscribe(String email) throws NamingException, SQLException {
        // Create a connection to the database
        InitialContext context = new InitialContext();
        DataSource dataSource = (DataSource)context.lookup("jdbc/mydb");
        Connection conn = dataSource.getConnection();      

        try {
            // Prepare an SQL statement to find the user in the database
            String sql = "SELECT * FROM users WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, email);

            // Execute the query and check if there are any results
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                // If there is a result, delete the user from the database
                String sql2 = "DELETE FROM users WHERE email = ?";
                PreparedStatement stmt2 = conn.prepareStatement(sql2);
                stmt2.setString(1, email);
                int rowsDeleted = stmt2.executeUpdate();
                if (rowsDeleted == 0) {
                    System.out.println("No rows were deleted.");
                } else {
                    System.out.println("The user was deleted from the database.");
                }
            } else {
                // If there are no results, return a message saying that the user is not subscribed
                System.out.println("You are not subscribed to our newsletter.");
            }
        } finally {
            // Close the connection to the database
            conn.close();
        }
    }
}