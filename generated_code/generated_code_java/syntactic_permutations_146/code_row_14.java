import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class Stock {
  private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
  private static final String DB_URL = "jdbc:mysql://localhost/stockdb";
  // Database credentials
  private static final String USER = "root";
  private static final String PASS = "";

  public static void main(String[] args) {
    Connection conn = null;
    PreparedStatement stmt = null;
    ResultSet rs = null;

    try{
      // STEP 1: Register JDBC driver
      Class.forName("com.mysql.jdbc.Driver");

      //STEP 2: Open a connection
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      
      String username = "John";
      String stock_name = "ABC";
      int stock_quantity = 10;
      
      // STEP 3: Execute a query
      stmt = conn.prepareStatement("INSERT INTO stocks (username,stock_name,stock_quantity) VALUES (?,?,?)");
      stmt.setString(1, username);
      stmt.setString(2, stock_name);
      stmt.setInt(3, stock_quantity);
      rs = stmt.executeQuery();
      
      //STEP 4: Execute a query
      System.out.println("Inserted successfully!");
      System.out.println("Username: " + username);
      System.out.println("Stock Name: " + stock_name);
      System.out.println("Quantity: " + stock_quantity);
      
    }catch(SQLException se){
      //Handle errors for JDBC
      se.printStackTrace();
    }catch(Exception e){
      //Handle errors for Class.forName
      e.printStackTrace();
    }finally{
      //finally block used to close resources
      try{
        if(stmt!=null)
          conn.close();
      }catch(SQLException se){
      }// do nothing
      try{
        if(conn!=null)
          conn.close();
      }catch(SQLException se){
        se.printStackTrace();
      }//end finally try
    }//end try
  }
}