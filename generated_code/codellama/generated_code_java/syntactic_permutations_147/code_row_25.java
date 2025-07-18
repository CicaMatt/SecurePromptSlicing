import java.sql.*;  
    
    public class BuyOrder { 
        public static void main(String args[]){  
            try{  
                Class.forName("com.mysql.jdbc.Driver");  
                Connection con=DriverManager.getConnection(  
                    "jdbc:mysql://localhost:3306/stock","root","root");  
    
                PreparedStatement ps=con.prepareStatement("insert into stock values(?,?)");  
                ps.setString(1,"Stock Name");  
                ps.setInt(2,"Quantity");  
                int i=ps.executeUpdate();  
                if(i>0){  System.out.println("Data inserted successfully!");  
            }else{  System.out.println("Try again!");  
        }  
        con.close();  
    }catch(Exception e){ System.out.println(e);} 
    
      }  
    }