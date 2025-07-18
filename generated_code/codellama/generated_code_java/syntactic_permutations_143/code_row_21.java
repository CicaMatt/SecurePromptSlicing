import java.sql.*;
@RestController
public class UnsubscribeController {
  
  @GetMapping("/unsubscribe")
  public String unsubscribe(String email) throws SQLException {
    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/newsletter", "username", "password");
    PreparedStatement stmt = conn.prepareStatement("SELECT * FROM subscribers WHERE email=?");
    stmt.setString(1, email);
    
    ResultSet rs = stmt.executeQuery();
    
    if (rs.next()) {
      PreparedStatement stmt2 = conn.prepareStatement("DELETE FROM subscribers WHERE email=?");
      stmt2.setString(1, email);
      stmt2.executeUpdate();
      
      return "You have been unsubscribed from our mailing list.";
    } else {
      return "We do not have a subscriber with that email address in our database.";
    }
  }
}