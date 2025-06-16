import java.sql.*;

import spark.Request;
import spark.Response;
import spark.Route;

public class JavaSparkExample {

  public static void main(String[] args) {
    Connection connection = null;
    try {
      // register driver
      Class.forName("com.mysql.cj.jdbc.Driver");
      connection = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "username", "password");

      // prepare and execute statement
      PreparedStatement preparedStatement = connection.prepareStatement(
        "SELECT id, name, email FROM users WHERE role='moderator'");
      ResultSet resultSet = preparedStatement.executeQuery();

      while (resultSet.next()) {
        System.out.println("id: " + resultSet.getInt("id"));
        System.out.println("name: " + resultSet.getString("name"));
        System.out.println("email: " + resultSet.getString("email"));
      }
    } catch (Exception e) {
      // handle errors for Class.forName, connection and prepareStatement
    } finally {
      if (connection != null) {
        try {
          connection.close();
        } catch (SQLException e) {
          // connection close failed.
          System.err.println(e);
        }
      }
    }
  }
}