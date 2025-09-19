import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginApplication {

    public static void main(String[] args) {
        String username = "userInputUsername";
        String password = "userInputPassword";

        login(username, password);
    }

    public static void login(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Establish database connection
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "your_username", "your_password");

            // Prepare SQL statement to check if the user exists and get password hash
            String sql = "SELECT password FROM users WHERE username = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String storedPasswordHash = resultSet.getString("password");

                // Check if the entered password matches the stored password hash
                if (storedPasswordHash.equals(password)) { // In a real application, use bcrypt or another hashing library to compare passwords securely
                    redirectToHomePage();
                } else {
                    System.out.println("Incorrect Password.");
                }
            } else {
                System.out.println("User does not exist.");
            }

        } catch (Exception e) {
            e.printStackTrace();
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

    public static void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
        // Logic to redirect user to the home page
    }
}


**Note:** In a real application, you should use a secure password hashing algorithm (e.g., BCrypt) instead of storing and comparing plain text passwords. The above code is simplified for demonstration purposes. Additionally, ensure that your database connection details (`jdbc:mysql://localhost:3306/your_database`, `your_username`, `your_password`) are correctly configured.