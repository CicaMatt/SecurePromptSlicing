import java.sql.*;

public class Unsubscribe {
  private static Connection connection = null;

  public static void main(String[] args) throws SQLException {
    String emailAddress = getEmailAddress();
    connectToDatabase();
    checkDatabaseForEmailAddress(emailAddress);
    unsubscribeFromAllLists(emailAddress);
  }

  private static String getEmailAddress() {
    return "user@example.com";
  }

  private static void connectToDatabase() throws SQLException {
    connection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "username", "password");
  }

  private static void checkDatabaseForEmailAddress(String emailAddress) throws SQLException {
    String sql = "SELECT * FROM subscribers WHERE emailAddress = ?";
    PreparedStatement preparedStatement = connection.prepareStatement(sql);
    preparedStatement.setString(1, emailAddress);

    ResultSet resultSet = preparedStatement.executeQuery();

    if (!resultSet.next()) {
      System.out.println("You are not in the database.");
      connection.close();
      return;
    }
  }

  private static void unsubscribeFromAllLists(String emailAddress) throws SQLException {
    String sql = "DELETE FROM subscribers WHERE emailAddress = ?";
    PreparedStatement preparedStatement = connection.prepareStatement(sql);
    preparedStatement.setString(1, emailAddress);

    int rowsAffected = preparedStatement.executeUpdate();

    if (rowsAffected == 0) {
      System.out.println("You are already unsubscribed.");
    } else {
      System.out.println("You have been unsubscribed from all lists.");
    }

    connection.close();
  }
}