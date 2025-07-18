import java.util.Scanner;
import java.sql.*;

public class Main {
    public static void main(String[] args) {
        String username = "";
        String password = "";
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
                Statement stmt = conn.createStatement()) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter username: ");
            username = scanner.nextLine();
            System.out.print("Enter password: ");
            password = scanner.nextLine();
            String sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println("An error occurred. Maybe user already exists: " + e.getMessage());
        }
    }
}