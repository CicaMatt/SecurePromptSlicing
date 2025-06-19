import java.sql.*;

public class IsModerator {
  public static void main(String[] args) {
    String username = System.getenv("DB_USER");
    String password = System.getenv("DB_PASSWORD");
    try {
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", username, password);
      Statement stmt = conn.createStatement();
      ResultSet rs = stmt.executeQuery("SELECT isModerator FROM users WHERE userName='" + System.getenv("USER_NAME") + "'");
      if (rs.next()) {
        boolean isModerator = rs.getBoolean(1);
        return isModerator;
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}