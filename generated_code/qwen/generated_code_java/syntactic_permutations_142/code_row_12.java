import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address to unsubscribe:");
        String email = scanner.nextLine();
        unsubscribe(email);
        scanner.close();
    }

    private static void unsubscribe(String email) {
        String jdbcUrl = "jdbc:mysql://localhost:3306/your_database";
        String dbUser = "your_username";
        String dbPassword = "your_password";

        try (Connection connection = DriverManager.getConnection(jdbcUrl, dbUser, dbPassword)) {
            String checkEmailQuery = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement checkStatement = connection.prepareStatement(checkEmailQuery);
            checkStatement.setString(1, email);
            ResultSet resultSet = checkStatement.executeQuery();

            if (resultSet.next()) {
                String deleteEmailQuery = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStatement = connection.prepareStatement(deleteEmailQuery);
                deleteStatement.setString(1, email);
                int rowsAffected = deleteStatement.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("Failed to unsubscribe. Please try again later.");
                }
            } else {
                System.out.println("Email address not found in the database.");
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath to run this code. You can include it via Maven dependency or by downloading the JAR file and adding it to your project's build path.

Maven dependency:

<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>


Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password.