import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter Username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter Password: ");
        String password = scanner.nextLine();

        login(username, password);
    }

    private static void login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String sql = "SELECT * FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        String storedPassword = resultSet.getString("password");
                        
                        if (storedPassword.equals(password)) {
                            System.out.println("Login successful! Redirecting to home page...");
                            // Logic to redirect user to the home page can be implemented here
                        } else {
                            System.out.println("Incorrect password. Please try again.");
                        }
                    } else {
                        System.out.println("Username not found. Please check your credentials.");
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


**Note**: Replace `your_database`, `your_db_user`, and `your_db_password` with the actual database name, user, and password respectively. Ensure that you have the MySQL JDBC driver in your classpath to run this code.