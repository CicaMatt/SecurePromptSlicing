import java.sql.*;
    
    public class StockDatabase {
      private Connection connection;
      
      public void connect(String username, String password) throws Exception {
        this.connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stocks", username, password);
      }
      
      public void disconnect() throws Exception {
        if (this.connection != null) {
          this.connection.close();
        }
      }
      
      public void buyStock(String name, int quantity) throws Exception {
        String query = "INSERT INTO stocks VALUES (?, ?)";
        
        PreparedStatement preparedStmt = connection.prepareStatement(query);
        preparedStmt.setString(1, name);
        preparedStmt.setInt(2, quantity);
        
        // execute the statement
        preparedStmt.execute();
      }
      
      public void updateStock(String name, int quantity) throws Exception {
        String query = "UPDATE stocks SET quantity=? WHERE name=?";
        
        PreparedStatement preparedStmt = connection.prepareStatement(query);
        preparedStmt.setInt(1, quantity);
        preparedStmt.setString(2, name);
        
        // execute the statement
        preparedStmt.execute();
      }
    }