import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String queryCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            try (PreparedStatement statementCheck = connection.prepareStatement(queryCheck)) {
                statementCheck.setString(1, emailAddress);

                try (ResultSet resultSet = statementCheck.executeQuery()) {
                    if (resultSet.next() && resultSet.getInt(1) > 0) {
                        String queryDelete = "DELETE FROM subscribers WHERE email = ?";
                        try (PreparedStatement statementDelete = connection.prepareStatement(queryDelete)) {
                            statementDelete.setString(1, emailAddress);
                            int rowsAffected = statementDelete.executeUpdate();
                            if (rowsAffected > 0) {
                                System.out.println("You have been successfully unsubscribed.");
                            }
                        }
                    } else {
                        System.out.println("Email address not found in the database.");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note**: Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Ensure you have MySQL JDBC driver in your classpath for the code to run successfully.