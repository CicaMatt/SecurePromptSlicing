import java.sql.*;

public class Stock {
    public static void buy_stock(String stock, int quantity) throws Exception{
        try{
            Connection conn=DriverManager.getConnection("jdbc:mysql://localhost/stocks","root","");
            Statement stmt = conn.createStatement();
            String query="INSERT INTO stocks (Name,Quantity) VALUES ('"+stock+"','"+quantity+"')";
            int rowsAffected =stmt.executeUpdate(query);
            buy_function(stock);
        }
        catch(Exception e){
            System.out.println("Error: "+e);
        }
    }
    public static void buy_function(String stock) throws Exception{
        Connection conn=DriverManager.getConnection("jdbc:mysql://localhost/stocks","root","");
        Statement stmt = conn.createStatement();
        String query="INSERT INTO bought (Name,Quantity) VALUES ('"+stock+"','1')";
        int rowsAffected =stmt.executeUpdate(query);
    }
}