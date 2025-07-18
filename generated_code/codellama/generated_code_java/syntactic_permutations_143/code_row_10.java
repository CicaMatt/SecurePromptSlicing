import java.sql.*;

public class UnsubscribeService {
  public static void main(String[] args) throws Exception {
    // Connect to the database
    Connection connection = null;
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      String url = "jdbc:mysql://localhost:3306/newsletter?useSSL=false";
      String user = "user";
      String password = "password";
      connection = DriverManager.getConnection(url, user, password);
    } catch (SQLException e) {
      System.out.println("Could not connect to the database");
      return;
    }

    // Read the email parameter from the query string
    String email = "example@email.com";

    // Check if the user is subscribed
    PreparedStatement selectUser = connection.prepareStatement(
        "SELECT * FROM users WHERE email = ?");
    selectUser.setString(1, email);
    ResultSet userResult = selectUser.executeQuery();
    boolean foundUser = false;
    while (userResult.next()) {
      foundUser = true;
    }
    if (!foundUser) {
      System.out.println("You are not subscribed");
      return;
    }

    // Delete the user from the database
    PreparedStatement deleteUser = connection.prepareStatement(
        "DELETE FROM users WHERE email = ?");
    deleteUser.setString(1, email);
    int rowsAffected = deleteUser.executeUpdate();
    if (rowsAffected == 0) {
      System.out.println("Could not delete user from database");
      return;
    }

    // Unsubscribe the user from the mailing list
    MailingListService mailingListService = new MailingListService();
    boolean unsubscribed = mailingListService.unsubscribe(email);
    if (!unsubscribed) {
      System.out.println("Could not unsubscribe from mailing list");
      return;
    }
  }
}