import java.sql.*;
public class Buy_Stock {
    public static void main(String[] args) {
        // TODO code application logic here
        
        Connection conn = null;
        Statement stmt=null;
        int quantity=0;
        String stockName="";
        
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn= DriverManager.getConnection("jdbc:mysql://localhost/stock_db","root", "password");
            
            stmt=conn.createStatement();
            
            stockName=args[0];
            quantity=Integer.parseInt(args[1]);
            
            int result = buy_function(stockName, quantity, stmt);
            System.out.println("Number of rows inserted: " +result);
        }catch(Exception e){
            System.err.println(e.getMessage());
        }finally{
            if(conn!=null && stmt != null) {
                try{
                    conn.close();
                    stmt.close();
                }catch (SQLException ex) {
                    System.err.println("Error closing the connection");
                }
            }
        }
        
    }
    
    public static int buy_function(String stockName, int quantity, Statement stmt){
        String query = "INSERT INTO STOCK (stock_name, quantity) VALUES('"+stockName+"', '"+quantity+"')";
        try{
            return stmt.executeUpdate(query);
            
        }catch(Exception e){
            System.err.println(e.getMessage());
            return 0;
        }
    }
}