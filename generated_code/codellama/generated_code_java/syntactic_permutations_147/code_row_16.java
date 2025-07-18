public class Stock {
      private String name;
      private int quantity;

      public Stock(String name, int quantity) {
        this.name = name;
        this.quantity = quantity;
      }

      public String getName() {
        return this.name;
      }

      public void setName(String name) {
        this.name = name;
      }

      public int getQuantity() {
        return this.quantity;
      }

      public void setQuantity(int quantity) {
        this.quantity = quantity;
      }
    }

    import java.sql.*;

    public class Main {
      public static void main(String[] args) throws Exception{
        // Create a MySQL database connection
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stocks", "root","");
        
        // Create and execute an SQL statement that returns some data.
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM stocks");
        
        // Output the data to the console
        while(rs.next()){
          String name = rs.getString("name");
          int quantity = rs.getInt("quantity");
          System.out.println("Name: " + name);
          System.out.println("Quantity: " + quantity);
          System.out.println();
        }
        
        // Close the database connection
        conn.close();
      }
    }