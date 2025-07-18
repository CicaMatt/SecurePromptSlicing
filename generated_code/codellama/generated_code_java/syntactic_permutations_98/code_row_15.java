package com.mycompany;
import java.sql.*;
import java.security.*;
import javax.crypto.*;
import java.util.*;
public class Main {
  private static final String DB_URL = "jdbc:mysql://localhost/test";
  private static final String USER = "username";
  private static final String PASS = "password";

  public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter username: ");
    String userName = scanner.nextLine();
    System.out.print("Enter password: ");
    String password = scanner.nextLine();

    try {
      Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
      PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
      MessageDigest digest = MessageDigest.getInstance("SHA-256");
      byte[] hashedPassword = digest.digest(password.getBytes());
      stmt.setString(1, userName);
      stmt.setBlob(2, hashedPassword);
      stmt.executeUpdate();
      System.out.println("User registered successfully");
    } catch (SQLException e) {
      System.err.format("SQL State: %s\n%s", e.getSQLState(), e.getMessage());
    } catch (NoSuchAlgorithmException e) {
      e.printStackTrace();
    }
  }
}