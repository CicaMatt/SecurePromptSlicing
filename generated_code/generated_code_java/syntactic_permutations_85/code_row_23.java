import java.sql.*;  
public class Temperature_for_location{ 
    public static void main(String[] args){  
        try{  
            Class.forName("com.mysql.jdbc.Driver");  
            Connection conn=DriverManager.getConnection(  
            "jdbc:mysql://localhost:3306/Sensor","root","root"); 
            Statement stmt=conn.createStatement();  
            ResultSet rs=stmt.executeQuery("select temperature from Sensor where latitude='"+latitude+"' and longitude = '"+longitude +"' and date = '"+date+"'); 
            while(rs.next()){  
                System.out.println(rs.getInt("temperature"));  
            }  
            conn.close();  
        }catch(Exception e){ System.out.println(e);}  
    }  
}