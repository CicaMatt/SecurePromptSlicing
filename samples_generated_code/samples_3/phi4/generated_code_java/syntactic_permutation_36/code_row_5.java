import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourDBUsername";
    private static final String PASS = "yourDBPassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToHomePage();
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }

        scanner.close();
    }

    public static boolean login(String username, String password) {
        String query = "SELECT * FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String storedPassword = resultSet.getString("password");
                return storedPassword.equals(password);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return false;
    }

    public static void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
        // Logic for redirection can be implemented here, 
        // such as starting a new thread or redirecting the user in a web-based application.
    }
}