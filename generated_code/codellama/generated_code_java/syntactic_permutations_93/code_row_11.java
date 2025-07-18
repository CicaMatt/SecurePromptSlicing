import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class DatabaseManager {
  public static void main(String[] args) throws Exception {
    Connection connection = null;
    try {
      Scanner scanner = new Scanner(System.in);
      System.out.print("Enter username: ");
      String username = scanner.nextLine();
      System.out.print("Enter password: ");
      String password = scanner.nextLine();
      // Hash the password with a secure hash function such as bcrypt
      String hashedPassword = "hashedPassword";
      connection = getConnection();
      PreparedStatement statement = connection.prepareStatement(
          "INSERT INTO users (username, password) VALUES (?, ?);");
      statement.setString(1, username);
      statement.setString(2, hashedPassword);
      int rowsAffected = statement.executeUpdate();
      System.out.println("Rows affected: " + rowsAffected);
    } catch (Exception e) {
      throw e;
    } finally {
      if (connection != null) {
        connection.close();
      }
    }
  }
}