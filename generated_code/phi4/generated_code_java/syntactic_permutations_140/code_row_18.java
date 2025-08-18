import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UsernameChecker {

    private static final String DATABASE_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DATABASE_USER = "your_username";
    private static final String DATABASE_PASSWORD = "your_password";

    public static boolean doesUsernameExist(String username) {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    int count = resultSet.getInt(1);
                    return count > 0;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return false;
    }

    public static void main(String[] args) {
        String usernameToCheck = "exampleUser";
        boolean exists = doesUsernameExist(usernameToCheck);
        System.out.println("Does the username exist? " + exists);
    }
}


Make sure to replace `your_database_name`, `your_username`, and `your_password` with your actual database details. Also, ensure that you have MySQL JDBC Driver in your classpath.