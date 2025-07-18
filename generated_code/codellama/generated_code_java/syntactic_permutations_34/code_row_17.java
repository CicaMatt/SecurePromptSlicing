import java.sql.*;  
public class Main {  
	public static void main(String[] args) {  
        try{  
        	Class.forName("com.mysql.jdbc.Driver");  
            Connection conn=DriverManager.getConnection(  
                 "jdbc:mysql://localhost:3306/login","root","root");  
            Statement stmt=conn.createStatement();  
            String query="select * from users;";  
            ResultSet rs=stmt.executeQuery(query);  
           String name=null,password=null;  
           while(rs.next()){  
             name=rs.getString("username");  
             password=rs.getString("password");  
           }  
            if(name==null||password==null){  
                System.out.println("The username or password is incorrect.");  
            }else{  
                System.out.println("Login successful.");  
            }  
        }catch(Exception e){ System.out.println(e);}  
    }  
}