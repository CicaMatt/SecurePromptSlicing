import java.sql.*;

public class ModeratorCheck {
  public static Boolean isModerator(String userId) throws SQLException {
    String connectionUrl = "jdbc:mysql://localhost:3306/mydb";
    Connection connection = null;

    Statement statement = null;
    ResultSet resultSet = null;
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      String username = System.getenv("DB_USERNAME");
      String password = System.getenv("DB_PASSWORD");

      connection = DriverManager.getConnection(connectionUrl, username, password);
      statement = connection.createStatement();
      resultSet = statement.executeQuery("SELECT userId FROM moderators WHERE userId=" + userId);
    } catch (ClassNotFoundException e) {
      e.printStackTrace();
    }

    return resultSet.next();
  }
}