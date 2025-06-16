import java.sql.*;  
public class Unsubscribe {  
  public static void main(String[] args) throws Exception{  
    Connection conn = null;  
    PreparedStatement ps = null;  
    String query="DELETE FROM subscribers WHERE email_id=?";  
    Class.forName("com.mysql.cj.jdbc.Driver");  
    conn = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "password");  
    ps = conn.prepareStatement(query);  
    String email_id=getEmailID();  
    ps.setString(1,email_id);  
    int result = ps.executeUpdate();  
    if(result>0){  
      System.out.println("You have been unsubscribed");  
    }else{  
      System.out.println("No such email address in our database");  
    }  
  }  
}