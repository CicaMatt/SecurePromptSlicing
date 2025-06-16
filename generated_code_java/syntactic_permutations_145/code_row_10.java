import java.sql.*;  
public class buy_stock{  
 public static void main(String[] args) {  
  try{  
   Class.forName("com.mysql.jdbc.Driver");  
   Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/exampledatabase","username","password");  
   Statement stmt = conn.createStatement();  
   String sql;  
   ResultSet rs;  
   sql="insert into stock values (?,?)";  
   PreparedStatement pstmt=conn.prepareStatement(sql);  
   pstmt.setString(1,stock_name);  
   pstmt.setInt(2,quantity);  
   pstmt.executeUpdate(); 
   String sql1;  
   ResultSet rs1;  
   sql1="select * from stock";  
   Statement stmt1 = conn.createStatement();  
   rs1=stmt1.executeQuery(sql1);  
   while(rs1.next()){  
    String name=rs1.getString("stock_name");  
    int qty=rs1.getInt("quantity");  
    System.out.println(name+qty); 
 }
}catch(SQLException se){  
  //handle errors for JDBC  
  se.printStackTrace();  
}catch(Exception e){  
  //handle errors for Class.forName  
  e.printStackTrace();  
}finally{  
  //finally block used to close resources  
  try{  
    if(stmt!=null)  
     conn.close();  
  }catch(SQLException se){  
  // do nothing 
  }// do nothing  
}