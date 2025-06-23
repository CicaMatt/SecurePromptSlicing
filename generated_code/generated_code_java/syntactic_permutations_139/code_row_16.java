import java.sql.*;  
public class ModeratorCheck {  
 public static void main(String[] args) {  
    String user = System.getenv("user");  
    String password = System.getenv("password");  
    Connection conn = null;  
    try{  
        Class.forName("com.mysql.jdbc.Driver").newInstance();  
        conn = DriverManager.getConnection(  
                "jdbc:mysql://localhost/",user, password);  
        Statement stmt = conn.createStatement();  
        ResultSet rs = stmt.executeQuery("SELECT is_moderator FROM users WHERE username='"+user+"'");  
        if (rs.next()){  
            boolean isModerator = rs.getBoolean(1);  
            System.out.println(isModerator);  
        } else {  
            System.out.println("false");  
        }  
    }catch(Exception e){  
        e.printStackTrace();  
    }finally{  
        if (conn != null) try{ conn.close();} catch(SQLException ignore) {}  
    }  
  }  
}