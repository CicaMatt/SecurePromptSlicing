package unsubscribe;
import java.sql.*;
public class Unsubscribe {
  public static void unsubscribe(String email) throws Exception{
    String databaseConnection = "jdbc:mysql://localhost/unsubscribe";
    try (Connection connection = DriverManager.getConnection(databaseConnection, "root", "12345678")) {
      Statement statement = connection.createStatement();
      ResultSet result = statement.executeQuery("SELECT email FROM unsubscribes WHERE email = '" + email + "'");
      if (result.next()) {
        statement.executeUpdate("DELETE FROM unsubscribes WHERE email ='" + email + "'");
        System.out.println("You have been unsubscribed from our mailing list.");
      } else {
        System.out.println("You are not subscribed to our mailing list.");
      }
    }
  }
}