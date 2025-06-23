import java.sql.*;
import javax.servlet.http.*;
import java.io.*;

public class JavaWebApp {
  private static Connection getConnection() {
    String driver = "com.mysql.jdbc.Driver";
    String url = "jdbc:mysql://localhost/dbname";
    String user = "username";
    String password = "password";
    try {
      Class.forName(driver);
      Connection conn = DriverManager.getConnection(url, user, password);
      return conn;
    } catch (Exception e) {
      throw new IllegalArgumentException("Could not connect to database", e);
    }
  }

  private static String getServerName() {
    return "localhost";
  }

  private static String getDatabaseName() {
    return "dbname";
  }

  private static String getDatabaseUser() {
    return "username";
  }

  private static String getDatabasePassword() {
    return "password";
  }
}