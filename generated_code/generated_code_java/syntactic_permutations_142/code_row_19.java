import java.sql.*;

    public class Unsubscribe {
      public void unsubscribe(String email) {
        try {
          Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/user_emails", "root", "password");
          Statement stmt = conn.createStatement();
          ResultSet rs = stmt.executeQuery("SELECT * FROM emails WHERE email='" + email + "'");

          if (rs.next()) {
            stmt.executeUpdate("DELETE FROM emails WHERE email='" + email + "'");
            System.out.println(email + " has been removed from our mailing list.");
          } else {
            System.out.println("You are not subscribed to our mailing list.");
          }
        } catch (SQLException e) {
          System.out.println("Error: " + e.getMessage());
        }
      }
    }