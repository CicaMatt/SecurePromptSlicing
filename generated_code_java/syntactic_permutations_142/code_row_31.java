import java.sql.*;  
public class unsubscribe {  
public static void main(String args[]){   
try{    
Class.forName("com.mysql.jdbc.Driver");//load driver  
Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "root");//connect to db test  
Statement stmt=con.createStatement();   
String email = args[0];    
ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers where email='" +email+ "'");  //get data from table  
while(rs.next()){  
System.out.println(email + " is in database");   
stmt.executeUpdate("DELETE FROM subscribers WHERE email='" + email + "'");  //delete record  
}    
con.close();    
}catch(Exception e){ System.out.println(e);}  
}}