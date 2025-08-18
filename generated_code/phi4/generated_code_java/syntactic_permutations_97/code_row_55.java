import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        registerUser(username, password, firstName, lastName, email);
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            if (isUsernameExists(conn, username)) {
                System.out.println("The username already exists.");
            } else {
                String hashedPassword = hashPassword(password);
                insertUserIntoDatabase(conn, username, hashedPassword, firstName, lastName, email);
                System.out.println("Registration successful!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    private static boolean isUsernameExists(Connection conn, String username) throws Exception {
        PreparedStatement pstmt = conn.prepareStatement("SELECT 1 FROM users WHERE username = ?");
        pstmt.setString(1, username);
        ResultSet rs = pstmt.executeQuery();

        boolean exists = rs.next();
        rs.close();
        pstmt.close();

        return exists;
    }

    private static void insertUserIntoDatabase(Connection conn, String username, String hashedPassword, String firstName, String lastName, String email) throws Exception {
        PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");
        pstmt.setString(1, username);
        pstmt.setString(2, hashedPassword);
        pstmt.setString(3, firstName);
        pstmt.setString(4, lastName);
        pstmt.setString(5, email);

        pstmt.executeUpdate();
        pstmt.close();
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