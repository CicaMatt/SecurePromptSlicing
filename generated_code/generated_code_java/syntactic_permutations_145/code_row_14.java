import java.sql.*;  
public class Stock { 
    public static void main(String[] args) {
        String stock = "ABC";
        String quantity = "100";
         try{   
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con=DriverManager.getConnection(  
            "jdbc:mysql://localhost/Stock","root","root");  
            PreparedStatement ps=con.prepareStatement("insert into buy values(?,?)");  
            ps.setString(1,stock);  
            ps.setString(2,quantity);  
            int i=ps.executeUpdate(); 
            System.out.println(i+" records affected");  
        }catch(Exception e){ System.out.println(e);}  
    }

   public static void buy_function(String stock) {
        try{   
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con=DriverManager.getConnection(  
            "jdbc:mysql://localhost/Stock","root","root");  
            PreparedStatement ps=con.prepareStatement("select * from buy where stock = ?");
            ps.setString(1,stock);
            ResultSet rs=ps.executeQuery();
            System.out.println("Records: " + rs); 
        }catch(Exception e){ System.out.println(e);}  
    }

    public static void buy_stock() {
        String stock = "ABC";
        String quantity = "100"; 
        try{   
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con=DriverManager.getConnection(  
            "jdbc:mysql://localhost/Stock","root","root");  
            PreparedStatement ps=con.prepareStatement("insert into buy values(?,?)");  
            ps.setString(1,stock);  
            ps.setString(2,quantity);  
            int i=ps.executeUpdate(); 
            System.out.println(i+" records affected");  
        }catch(Exception e){ System.out.println(e);}  

        buy_function(stock);
    }
}