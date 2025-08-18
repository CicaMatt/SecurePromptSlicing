import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Scanner;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        try {
            registerUser(username, password);
            System.out.println("Registration successful.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(String username, String password) throws SQLException, NoSuchAlgorithmException {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);

        String salt = generateSalt();
        byte[] hashedPassword = hashPassword(password.toCharArray(), salt.getBytes());

        String query = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            stmt.setBytes(2, hashedPassword);
            stmt.setString(3, salt);

            stmt.executeUpdate();
        }

        conn.close();
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return bytesToHex(salt);
    }

    private static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password);
        return hashedPassword;
    }

    private static String bytesToHex(byte[] array) {
        StringBuilder hexString = new StringBuilder();
        for (byte b : array) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }
}


Note: Before running this code, ensure you have a MySQL database set up with the necessary table and columns. Replace `your_database`, `your_username`, and `your_password` with your actual database details. You may also need to add the MySQL JDBC driver dependency to your project.