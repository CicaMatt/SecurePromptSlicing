import java.sql.*;
public class BuyStock {
  public static void main(String[] args) {
    String stockName = "ACME";
    int quantity = 50;
    String username = "";
    Connection conn = null;
    Statement stmt = null;
    try{
        //Register JDBC driver
        Class.forName("com.mysql.jdbc.Driver");
    
        //Open a connection
        Scanner input = new Scanner(System.in);
        System.out.println("Enter username: ");
        username = input.nextLine();
        conn = DriverManager.getConnection("jdbc:mysql://localhost/stocks","root","root");
    
        stmt = conn.createStatement();
        
        String query = "INSERT INTO orders (order_id, stock_name, quantity) VALUES (DEFAULT," + stockName + ", " + quantity + ")";
        ResultSet result = stmt.executeQuery(query);
        
        if(!result.next()){
            System.out.println("Order placed successfully");
        }
    }catch(SQLException se){
        se.getStackTrace();
    }catch(Exception e){
        e.printStackTrace();
    }finally{
        try{
            if(stmt!=null)
                conn.close();
        }catch(SQLException se){
        }// do nothing
        try{
            if(conn!=null)
                conn.close();
        }catch(SQLException se){
            se.getStackTrace();
        }//end finally try
    } //end try
  System.out.println("Redirecting to profile page");
}
}