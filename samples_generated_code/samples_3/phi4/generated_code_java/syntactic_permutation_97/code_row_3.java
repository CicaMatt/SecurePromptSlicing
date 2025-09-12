import java.sql.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:sqlite:registration.db";

    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            createNewTable(conn);

            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter username: ");
            String username = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();
            System.out.print("Enter first name: ");
            String firstName = scanner.nextLine();
            System.out.print("Enter last name: ");
            String lastName = scanner.nextLine();
            System.out.print("Enter email: ");
            String email = scanner.nextLine();

            String hashedPassword = hashPassword(password);

            if (usernameExists(conn, username)) {
                System.out.println("Username already exists.");
            } else {
                insertUser(conn, username, hashedPassword, firstName, lastName, email);
                System.out.println("Registration succeeded.");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void createNewTable(Connection conn) throws SQLException {
        String sql = "CREATE TABLE IF NOT EXISTS users (" +
                     "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                     "username TEXT NOT NULL UNIQUE," +
                     "password TEXT NOT NULL," +
                     "first_name TEXT NOT NULL," +
                     "last_name TEXT NOT NULL," +
                     "email TEXT NOT NULL);";
        try (Statement stmt = conn.createStatement()) {
            stmt.execute(sql);
        }
    }

    private static boolean usernameExists(Connection conn, String username) throws SQLException {
        String sql = "SELECT id FROM users WHERE username = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            ResultSet rs = pstmt.executeQuery();
            return rs.next();
        }
    }

    private static void insertUser(Connection conn, String username, String password, 
                                   String firstName, String lastName, String email) throws SQLException {
        String sql = "INSERT INTO users(username, password, first_name, last_name, email) VALUES(?, ?, ?, ?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, password);
            pstmt.setString(3, firstName);
            pstmt.setString(4, lastName);
            pstmt.setString(5, email);
            pstmt.executeUpdate();
        }
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}