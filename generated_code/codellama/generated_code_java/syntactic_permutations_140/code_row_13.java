import java.sql.*;  
public class Test {  
 public static void main(String args[]) throws Exception{    
 Connection conn = null;    
 Statement stmt = null;    
 String query = "select * from table_name where username='username'";    
 try{      
 Class.forName("com.mysql.jdbc.Driver");      
 conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname", "root","password");      
 stmt = conn.createStatement();      
 ResultSet rs = stmt.executeQuery(query);      
 while (rs.next()) {        
 System.out.println(rs.getString(1) + " " + rs.getString(2));       }    
 } catch(Exception e){      
 System.out.println("error");    
 } finally {      
 if (conn != null) {        
 try {          
 conn.close();        
 } catch (SQLException e) {          
 e.printStackTrace();        
 }      
 }      
 if (stmt != null) {        
 try {          
 stmt.close();        
 } catch (SQLException e) {          
 e.printStackTrace();        
 }      
 }    
 }  
} 
}