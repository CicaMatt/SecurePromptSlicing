import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginSystem {
    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String username = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            System.out.println("Connection failed!");
            e.printStackTrace();
            return null;
        }
    }

    public boolean login(String username, String password) {
        String query = "SELECT * FROM users WHERE username = ?";
        try (Connection conn = connect(); PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                String storedPassword = rs.getString("password");
                if (storedPassword.equals(password)) {
                    redirectToHomePage();
                    return true;
                } else {
                    System.out.println("Incorrect password.");
                }
            } else {
                System.out.println("Username not found.");
            }
        } catch (SQLException e) {
            System.out.println("Login failed!");
            e.printStackTrace();
        }
        return false;
    }

    private void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
    }

    public static void main(String[] args) {
        LoginSystem ls = new LoginSystem();
        ls.login("user1", "pass123");
    }
}