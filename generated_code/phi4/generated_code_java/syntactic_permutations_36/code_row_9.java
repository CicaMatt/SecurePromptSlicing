import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        login(username, password);

        scanner.close();
    }

    public static void login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String query = "SELECT * FROM users WHERE username = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);

                ResultSet resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    String storedPassword = resultSet.getString("password");

                    if (storedPassword.equals(password)) {
                        System.out.println("Login successful! Redirecting to home page...");
                        // Redirect to the home page
                        redirectToHomePage();
                    } else {
                        System.out.println("Incorrect password.");
                    }
                } else {
                    System.out.println("Username does not exist.");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void redirectToHomePage() {
        // Implement redirection logic here
        System.out.println("Welcome to the Home Page!");
    }
}


**Note:** Replace `your_database_name`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that you have the MySQL JDBC driver in your classpath.