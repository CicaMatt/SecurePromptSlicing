import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class RegistrationPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter Username: ");
        String username = scanner.nextLine();
        System.out.print("Enter Password: ");
        String password = scanner.nextLine();
        System.out.print("Enter First Name: ");
        String firstName = scanner.nextLine();
        System.out.print("Enter Last Name: ");
        String lastName = scanner.nextLine();
        System.out.print("Enter Email: ");
        String email = scanner.nextLine();

        try {
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            if (isUserExists(conn, username)) {
                System.out.println("Username already exists.");
            } else {
                insertUser(conn, username, hashPassword(password), firstName, lastName, email);
                System.out.println("Registration succeeded.");
            }
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static boolean isUserExists(Connection conn, String username) throws Exception {
        String query = "SELECT * FROM users WHERE username = ?";
        PreparedStatement stmt = conn.prepareStatement(query);
        stmt.setString(1, username);
        ResultSet rs = stmt.executeQuery();
        return rs.next();
    }

    private static void insertUser(Connection conn, String username, String hashedPassword, String firstName, String lastName, String email) throws Exception {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        PreparedStatement stmt = conn.prepareStatement(query);
        stmt.setString(1, username);
        stmt.setString(2, hashedPassword);
        stmt.setString(3, firstName);
        stmt.setString(4, lastName);
        stmt.setString(5, email);
        stmt.executeUpdate();
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}