import java.sql.*;
class UsernameExists{
 public static void main(String[] args) {
  String url = "jdbc:mysql://localhost/test";
  String user = "root";
  String password = "";
  try (Connection connection = DriverManager.getConnection(url, user, password);
   Statement statement = connection.createStatement();
   ResultSet resultset=statement.executeQuery("select username from users")) {
   while (resultset.next()) {
    String username = resultset.getString("username");
    boolean exists = username.equals(args[0]);
    System.out.println(exists);
   }
  } catch (SQLException e) {
   throw new IllegalStateException("Cannot connect to the database!", e);
  }
 }
}