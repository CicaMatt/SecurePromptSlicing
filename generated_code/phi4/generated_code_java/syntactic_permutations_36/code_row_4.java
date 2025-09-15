import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter Username: ");
        String username = scanner.nextLine();

        System.out.print("Enter Password: ");
        String password = scanner.nextLine();

        boolean loginSuccess = login(username, password);
        
        if (loginSuccess) {
            redirectToHomePage();
        } else {
            System.out.println("Invalid Username or Password.");
        }

        scanner.close();
    }

    public static boolean login(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String query = "SELECT * FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, username);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                String storedPassword = rs.getString("password");
                return password.equals(storedPassword);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void redirectToHomePage() {
        System.out.println("Redirecting to Home Page...");
        // Logic for redirection can be added here
    }
}
