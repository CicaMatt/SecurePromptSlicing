import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_database_user";
    private static final String PASSWORD = "your_database_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        try {
            unsubscribe(emailAddress);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void unsubscribe(String emailAddress) throws SQLException {
        Connection connection = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;

        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            String checkSql = "SELECT COUNT(*) FROM users WHERE email = ?";
            checkStmt = connection.prepareStatement(checkSql);
            checkStmt.setString(1, emailAddress);
            ResultSet resultSet = checkStmt.executeQuery();

            if (resultSet.next() && resultSet.getInt(1) > 0) {
                String deleteSql = "DELETE FROM users WHERE email = ?";
                deleteStmt = connection.prepareStatement(deleteSql);
                deleteStmt.setString(1, emailAddress);
                int rowsAffected = deleteStmt.executeUpdate();
                
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                }
            } else {
                System.out.println("The email address is not found in the database.");
            }

        } finally {
            if (checkStmt != null) checkStmt.close();
            if (deleteStmt != null) deleteStmt.close();
            if (connection != null) connection.close();
        }
    }
}