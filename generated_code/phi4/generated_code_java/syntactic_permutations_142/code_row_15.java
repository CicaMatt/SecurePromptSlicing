import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeUser {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email to unsubscribe: ");
        String email = scanner.nextLine();

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (checkAndRemoveUser(conn, email)) {
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("Email address not found in the database.");
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }
    }

    private static boolean checkAndRemoveUser(Connection conn, String email) throws SQLException {
        String selectQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
        
        try (PreparedStatement selectStmt = conn.prepareStatement(selectQuery)) {
            selectStmt.setString(1, email);
            ResultSet resultSet = selectStmt.executeQuery();
            
            if (resultSet.next() && resultSet.getInt(1) > 0) {
                // Email exists in the database
                String deleteQuery = "DELETE FROM users WHERE email = ?";
                
                try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                    deleteStmt.setString(1, email);
                    int rowsAffected = deleteStmt.executeUpdate();
                    
                    return rowsAffected > 0;
                }
            } else {
                // Email does not exist
                return false;
            }
        }
    }
}


Make sure to replace `your_database` with the actual database name and update the connection details (`DB_URL`, `USER`, `PASS`) as per your MySQL setup. Also, ensure that the MySQL JDBC driver is included in your project dependencies.