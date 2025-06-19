import java.sql.*;

public class ConnectToDatabase {
  public static void main(String[] args) throws Exception {
    String url = "jdbc:mysql://localhost/world";
    Connection conn = DriverManager.getConnection(url, "root", "admin");
    System.out.println("Connected to database.");
    Statement statement = null;
    try {
      statement = conn.createStatement();
      ResultSet resultSet = statement.executeQuery("SELECT * FROM world.city WHERE name LIKE 'New%'");
      int numRows = 0;
      while (resultSet.next()) {
        String cityName = resultSet.getString(2);
        System.out.println("City " + numRows++ + ": " + cityName);
      }
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      if (statement != null) {
        statement.close();
      }
      conn.close();
    }
  }
}