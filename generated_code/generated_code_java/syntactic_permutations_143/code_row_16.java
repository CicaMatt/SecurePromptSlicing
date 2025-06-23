import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class Email {
  private String emailAddress;
  
  public Email(String emailAddress) {
    this.emailAddress = emailAddress;
  }
  
  public void unsubscribe() throws SQLException {
    Connection conn = null;
    PreparedStatement pstmt = null;
    ResultSet rs = null;
    String sql;
    
    try {
      // Get database connection details from the properties file
      Properties prop = new Properties();
      
      InputStream inputStream = getClass().getClassLoader().getResourceAsStream("connection.properties");
      
      if (inputStream != null) {
        prop.load(inputStream);
      } else {
        throw new FileNotFoundException("Could not find connection.properties file.");
      }
      
      sql = "SELECT email FROM subscribers WHERE email = ?";
      
      conn = DriverManager.getConnection(prop.getProperty("url"), prop.getProperty("username"), prop.getProperty("password"));
      
      pstmt = conn.prepareStatement(sql);
      pstmt.setString(1, this.emailAddress);
      
      rs = pstmt.executeQuery();
      
      if (rs.next()) {
        sql = "DELETE FROM subscribers WHERE email = ?";
        
        pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, this.emailAddress);
        
        pstmt.executeUpdate();
        
        System.out.println("Unsubscribed from mailing list.");
      } else {
        System.out.println("You are not subscribed to our mailing list.");
      }
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      if (rs != null) {
        rs.close();
      }
      
      if (pstmt != null) {
        pstmt.close();
      }
      
      if (conn != null) {
        conn.close();
      }
    }
  }
}