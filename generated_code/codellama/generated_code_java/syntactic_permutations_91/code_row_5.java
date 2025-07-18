import java.sql.*;
import java.util.*;

// Simple web application to register users for an account.
public class WebApp {
  public static void main(String[] args) {
    // Connect to the database
    Connection conn = getConnection();

    // Create a statement object
    Statement stmt = null;
    try {
      stmt = conn.createStatement();

      // Get the username and password from the user
      String username = getUsername();
      String password = getPassword();

      // Hash the password before storing it in the database
      String hashedPassword = hashPassword(password);

      // Insert the username and hashed password into the database
      stmt.executeUpdate("INSERT INTO users (username, password) VALUES ('" + username + "', '" + hashedPassword + "')");

    } catch (SQLException e) {
      System.out.println(e.getMessage());
    } finally {
      // Close the statement and connection objects to prevent leaks
      try {
        if (stmt != null) stmt.close();
        if (conn != null) conn.close();
      } catch (SQLException e) {
        System.out.println(e.getMessage());
      }
    }
  }

  // Get the username from the user
  private static String getUsername() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter username: ");
    return sc.nextLine();
  }

  // Get the password from the user
  private static String getPassword() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter password: ");
    return sc.nextLine();
  }

  // Hash a given password using SHA-256
  private static String hashPassword(String password) {
    try {
      MessageDigest digest = MessageDigest.getInstance("SHA-256");
      byte[] hashedBytes = digest.digest(password.getBytes());
      return new String(hashedBytes);
    } catch (NoSuchAlgorithmException e) {
      throw new RuntimeException(e);
    }
  }

  // Get a connection to the database
  private static Connection getConnection() {
    try {
      Class.forName("com.mysql.jdbc.Driver");
      return DriverManager.getConnection("jdbc:mysql://localhost/webapp", "root", "password");
    } catch (ClassNotFoundException | SQLException e) {
      throw new RuntimeException(e);
    }
  }
}