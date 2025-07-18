import java.sql.*;
import javax.sql.*;
import org.sqlite.*;

public class App {
  private static Connection connection;
  private static String name = "Mira";
  private static String dbName = "my_database.db";
  private static String user = "user123";
  private static String password = "pass456";

  public static void main(String[] args) throws Exception {
    connection = getConnection();
  }

  public static Connection getConnection() {
    try {
      Class.forName("org.sqlite.JDBC");
      return DriverManager.getConnection("jdbc:sqlite:" + dbName);
    } catch (Exception e) {
      System.out.println(e);
    }
  }

  public static String getName() {
    return name;
  }

  public static String getDbName() {
    return dbName;
  }

  public static String getUser() {
    return user;
  }

  public static String getPassword() {
    return password;
  }
}