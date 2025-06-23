import java.sql.*;
public class Unsubscribe {
  public static void main(String[] args) throws Exception {
    Class.forName("com.mysql.jdbc.Driver");
    Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
    String emailAddress = args[0];
    Statement statement = connection.createStatement();
    ResultSet resultSet = statement.executeQuery(
      "SELECT * FROM subscribers WHERE email_address=" + emailAddress);
    if (resultSet.next()) {
      statement.executeUpdate("DELETE FROM subscribers WHERE email_address=" + emailAddress);
      System.out.println("You have been unsubscribed");
    } else {
      System.out.println("Your email address is not in our database");
    }
  }
}