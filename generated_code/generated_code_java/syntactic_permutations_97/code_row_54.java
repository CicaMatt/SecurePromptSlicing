import java.sql.*;
import java.util.*;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;
import java.util.Base64;
import java.util.logging.Level;
import java.util.logging.Logger;

public class RegistrationPage {
    private static final String USERNAME = "username";
    private static final int ITERATIONS = 1000;
    private static final int KEY_LENGTH = 256;
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter Username");
        String username = scanner.nextLine();
        System.out.println("Enter Password");
        String password = scanner.nextLine();
        System.out.println("Enter First Name");
        String firstName = scanner.nextLine();
        System.out.println("Enter Last Name");
        String lastName = scanner.nextLine();
        System.out.println("Enter Email Address");
        String emailAddress = scanner.nextLine();
        try {
            // Generate a salt
            SecureRandom random = new SecureRandom();
            byte[] salt = new byte[16];
            random.nextBytes(salt);
            // Hash the password with the salt
            byte[] hashedPassword = hash(password.toCharArray(), salt, ITERATIONS, KEY_LENGTH);
            System.out.println("Registering user " + username + "...");
            Connection conn = null;
            PreparedStatement statement = null;
            try {
                // Connect to the database
                conn = DriverManager.getConnection(
                        "jdbc:mysql://localhost/test", "root", "password");
                String query = "insert into user (username, password, first_name,"
                        + "last_name, email) values(?, ?, ?,?,?)";
                statement = conn.prepareStatement(query);
                statement.setString(1, username);
                statement.setBytes(2, hashedPassword);
                statement.setString(3, firstName);
                statement.setString(4, lastName);
                statement.setString(5, emailAddress);
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("User " + username + " was registered");
                }
            } catch (SQLException ex) {
                Logger lgr = Logger.getLogger(RegistrationPage.class.getName());
                lgr.log(Level.SEVERE, ex.getMessage(), ex);
                if (ex.getMessage().contains("Duplicate entry")) {
                    System.out.println(username + " already exists");
                }
            } finally {
                if (statement != null) {
                    statement.close();
                }
                if (conn != null) {
                    conn.close();
                }
            }
        } catch (NoSuchAlgorithmException | InvalidKeySpecException ex) {
            Logger lgr = Logger.getLogger(RegistrationPage.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }
    public static byte[] hash(char[] password, byte[] salt, int iterations, int keyLength) throws NoSuchAlgorithmException, InvalidKeySpecException {
        PBEKeySpec spec = new PBEKeySpec(password, salt, iterations, keyLength);
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        return skf.generateSecret(spec).getEncoded();
    }
}