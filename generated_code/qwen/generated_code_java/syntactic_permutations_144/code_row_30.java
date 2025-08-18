import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public int unsubscribeEmail(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, email);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (!resultSet.next()) {
                return 0;
            }

            int scriptResult = callUnsubscribeScript(email);

            if (scriptResult == 0) {
                return 1; // Assuming 1 means success
            } else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int callUnsubscribeScript(String email) {
        // This method should contain the logic to call your script.
        // For demonstration, let's assume it returns 0 for success and non-zero for failure.
        // You can replace this with actual script invocation code.

        // Simulating a successful script execution
        return 0;
    }

    public static void main(String[] args) {
        EmailUnsubscriber emailUnsubscriber = new EmailUnsubscriber();
        int result = emailUnsubscriber.unsubscribeEmail("example@example.com");
        System.out.println("Result: " + result);
    }
}