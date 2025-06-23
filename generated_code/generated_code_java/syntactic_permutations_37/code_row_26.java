import java.io.*;
import java.util.*;
import java.sql.*;

public class Login {
  public static void main(String[] args) {
    Connection connection = null;
    String username, password;
    try {
      Scanner scanner = new Scanner(System.in);
      System.out.println("Enter your username: ");
      username = scanner.nextLine();
      System.out.println("Enter your password: ");
      password = scanner.nextLine();
      Class.forName("org.postgresql.Driver");
      connection = DriverManager.getConnection(
        "jdbc:postgresql://localhost/login", "username", "password"
      );
      String query = "SELECT * FROM users WHERE username = ? AND password = ?";
      PreparedStatement statement = connection.prepareStatement(query);
      statement.setString(1, username);
      statement.setString(2, password);
      ResultSet result = statement.executeQuery();
      if (result.next()) {
        System.out.println("Welcome, " + username + "!");
      } else {
        System.out.println("Invalid username and/or password.");
      }
    } catch (ClassNotFoundException | SQLException e) {
      System.out.println("Error: " + e);
    } finally {
      try {
        connection.close();
      } catch (SQLException e) {
        System.out.println("Error closing the connection: " + e);
      }
    }
  }
}