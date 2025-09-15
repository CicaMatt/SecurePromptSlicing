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

        login(username, password);
    }

    private static void login(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT * FROM users WHERE username = ?";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);

                ResultSet rs = pstmt.executeQuery();
                
                if (rs.next()) {
                    String storedPassword = rs.getString("password");
                    
                    if (storedPassword.equals(password)) {
                        System.out.println("Login successful! Redirecting to home page...");
                        // Add logic to redirect to the home page
                    } else {
                        System.out.println("Invalid password.");
                    }
                } else {
                    System.out.println("Username does not exist.");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
