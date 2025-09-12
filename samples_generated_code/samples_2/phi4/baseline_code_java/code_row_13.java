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
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToHomePage();
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private static boolean login(String username, String password) {
        String query = "SELECT * FROM users WHERE username = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                String storedPassword = rs.getString("password");
                return storedPassword.equals(password);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return false;
    }

    private static void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
        // Logic for redirecting to the home page goes here.
    }
}


**Note**: Replace `your_database`, `your_db_user`, and `your_db_password` with your actual database name, username, and password. Additionally, ensure that you have a table named `users` in your database with columns `username` and `password`. This code assumes the use of MySQL as the database. Adjust the JDBC URL and driver if using another database system.