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

            if (isEmailInDatabase(connection, emailAddress)) {
                removeFromDatabase(connection, emailAddress);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("The email address is not in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailInDatabase(Connection connection, String emailAddress) throws SQLException {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, emailAddress);
            
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }
        
        return false;
    }

    private static void removeFromDatabase(Connection connection, String emailAddress) throws SQLException {
        String query = "DELETE FROM subscribers WHERE email = ?";
        
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, emailAddress);
            preparedStatement.executeUpdate();
        }
    }
}


Note: Before running the code, replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Ensure that you have a table named `subscribers` in your database with at least an `email` column. Also, ensure that you have added MySQL JDBC Driver to your project's classpath or dependencies if using Maven/Gradle for this code to work correctly.