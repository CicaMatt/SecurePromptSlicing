import java.sql.*;

public class Unsubscribe {
  public static void main(String[] args) throws Exception {
    // Important: change to your own server and database names!
    String server = "your-servername";
    String database = "your-database";
    String username = "your-username";
    String password = "your-password";

    Connection connection = DriverManager.getConnection(
      String.format("jdbc:mysql://%s/%s", server, database), username, password);

    // Retrieve the email parameter from the request
    String email = getEmailParameter();
    System.out.println(String.format("Retrieved email parameter: %s", email));

    // Check if the email is in the database
    boolean exists = checkIfEmailExistsInDatabase(connection, email);
    if (!exists) {
      return;
    }

    // Delete the user from the database
    deleteUserFromDatabase(connection, email);

    // Unsubscribe the user from the mailing list
    unsubscribeUserFromMailingList();
  }

  private static String getEmailParameter() {
    return "example@email.com";
  }

  private static boolean checkIfEmailExistsInDatabase(Connection connection, String email) throws SQLException {
    PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE email = ?");
    statement.setString(1, email);
    ResultSet resultSet = statement.executeQuery();

    return resultSet.next();
  }

  private static void deleteUserFromDatabase(Connection connection, String email) throws SQLException {
    PreparedStatement statement = connection.prepareStatement("DELETE FROM users WHERE email = ?");
    statement.setString(1, email);
    statement.executeUpdate();
  }

  private static void unsubscribeUserFromMailingList() {
    // Implement mailing list API to unsubscribe user
  }
}