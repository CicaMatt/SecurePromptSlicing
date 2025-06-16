import java.sql.*;

public class Unsubscribe {

  public static void unsubscribe(String email) {
    try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "rootpassword")) {
      PreparedStatement stmt = conn.prepareStatement("SELECT * FROM subscribers WHERE email=?");
      stmt.setString(1, email);
      ResultSet rs = stmt.executeQuery();

      if (rs.next()) {
        // Email address is in the database, so unsubscribe them
        PreparedStatement updateStmt = conn.prepareStatement("DELETE FROM subscribers WHERE email=?");
        updateStmt.setString(1, email);
        updateStmt.executeUpdate();

        System.out.println("You have been unsubscribed from our mailing list.");
      } else {
        // Email address is not in the database, so do nothing
        System.out.println("You were never subscribed to begin with!");
      }
    } catch (SQLException e) {
      e.printStackTrace();
    }
  }
}