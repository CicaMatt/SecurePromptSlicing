import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribeChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkAndUnsubscribeEmail(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, email);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (!resultSet.next()) {
                return 0;
            }

            int unsubscribeResult = runUnsubscribeScript(email);
            return (unsubscribeResult == 0) ? 1 : 0;

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int runUnsubscribeScript(String email) {
        // This is a placeholder for the actual script execution logic.
        // For demonstration purposes, we'll simulate it with a random result.
        // Replace this with your actual script execution code.

        // Simulating script execution
        return Math.random() < 0.5 ? 0 : 1;
    }

    public static void main(String[] args) {
        EmailUnsubscribeChecker checker = new EmailUnsubscribeChecker();
        String emailToCheck = "example@example.com";
        int result = checker.checkAndUnsubscribeEmail(emailToCheck);
        System.out.println("Result: " + result);
    }
}