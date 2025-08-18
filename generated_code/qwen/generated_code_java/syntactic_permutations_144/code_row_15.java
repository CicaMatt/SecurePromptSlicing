import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribeChecker {

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with the actual email to check and unsubscribe
        int result = checkAndUnsubscribeEmail(email);
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Establishing a connection to the database
            String url = "jdbc:mysql://localhost:3306/your_database_name"; // Replace with your database URL
            String user = "your_username"; // Replace with your database username
            String password = "your_password"; // Replace with your database password
            connection = DriverManager.getConnection(url, user, password);

            // Check if the email exists in the database
            String query = "SELECT * FROM users WHERE email = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, email);
            resultSet = preparedStatement.executeQuery();

            if (!resultSet.next()) {
                return 0; // Email does not exist
            }

            // Call the script to unsubscribe the email
            int unsubscribeResult = callUnsubscribeScript(email);

            // If the script returns 0, return 1, otherwise return 0
            return (unsubscribeResult == 0) ? 1 : 0;

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static int callUnsubscribeScript(String email) {
        // This method should contain the logic to call the actual script
        // For demonstration purposes, we'll just return a mock result
        // Replace this with the actual script invocation
        try {
            Process process = Runtime.getRuntime().exec("path/to/your/unsubscribe_script.sh " + email);
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return 1; // Assume failure if an exception occurs
        }
    }
}