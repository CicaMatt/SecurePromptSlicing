import java.sql.*;
import java.util.Scanner;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.SecretKeyFactory;
import org.apache.commons.codec.binary.Base64;

public class Registration {

  // JDBC driver name and database URL
  static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
  static final String DB_URL = "jdbc:mysql://localhost/mydatabase";

  //  Database credentials
  static final String USER = "username";
  static final String PASS = "password";

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter username: ");
    String userName = scanner.nextLine();
    System.out.print("Enter password: ");
    String passWord = scanner.nextLine();
    System.out.print("Enter first name: ");
    String fname = scanner.nextLine();
    System.out.print("Enter last name: ");
    String lname = scanner.nextLine();
    System.out.print("Enter email: ");
    String email = scanner.nextLine();

    // Check if username exists in database
    String sql = "SELECT * FROM users WHERE username = ?";

    Connection conn = null;
    PreparedStatement pstmt = null;
    ResultSet rs = null;

    try {
      // Register JDBC driver
      Class.forName(JDBC_DRIVER);

      // Open a connection
      conn = DriverManager.getConnection(DB_URL, USER, PASS);

      // Create prepared statement
      pstmt = conn.prepareStatement(sql);

      // Set parameters
      pstmt.setString(1, userName);

      // Execute query
      rs = pstmt.executeQuery();

      if (rs.next()) {
        System.out.println("Username already exists");
      } else {
        String hashedPassword = generateStrongPasswordHash(passWord);
        sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";

        // Create prepared statement
        pstmt = conn.prepareStatement(sql);

        // Set parameters
        pstmt.setString(1, userName);
        pstmt.setString(2, hashedPassword);
        pstmt.setString(3, fname);
        pstmt.setString(4, lname);
        pstmt.setString(5, email);

        // Execute insert
        int result = pstmt.executeUpdate();

        if (result == 1) {
          System.out.println("Registration successful");
        } else {
          System.out.println("Registration failed");
        }
      }
    } catch (SQLException e) {
      e.printStackTrace();
    } finally {
      try {
        if (rs != null)
          rs.close();

        if (pstmt != null)
          pstmt.close();

        if (conn != null)
          conn.close();
      } catch (SQLException ex) {
        System.out.println("Database connection failed.");
      }
    }
  }

  public static String generateStrongPasswordHash(String password) {
    try {
      byte[] salt = SecureRandom.getInstance("SHA1PRNG").generateSeed(8);
      // Storing salt with the password
      return Base64.encodeBase64String(salt) + "$" + hashPassword(password, salt);
    } catch (Exception e) {
      throw new IllegalStateException("Could not generate strong password hash", e);
    }
  }

  private static String hashPassword(String password, byte[] salt) throws Exception {
    if (password == null || password.length() == 0) {
      throw new IllegalArgumentException("Empty passwords are not supported.");
    }

    SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
    PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), salt, 65536, 128);

    return Base64.encodeBase64String(f.generateSecret(spec).getEncoded());
  }
}