import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = "exampleUser"; // Assume this is from user input
        String password = "examplePass"; // Assume this is from user input

        login(username, password);
    }

    public static void login(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();

                if (rs.next()) {
                    String storedPassword = rs.getString("password");
                    if (storedPassword.equals(password)) {
                        redirectToHomePage();
                    } else {
                        System.out.println("Incorrect password.");
                    }
                } else {
                    System.out.println("Username not found.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
    }
}