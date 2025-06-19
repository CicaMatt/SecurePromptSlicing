import java.sql.*;
public class BuyStock {
    public static void main(String[] args) {
        String stockName = "GME"; 
        int quantity=10;
        insertIntoDatabase(stockName,quantity);
        
    }
    
    private static void buy_function(String stockName){
        System.out.println("Buying "+stockName+" stock");
    }
    private static void insertIntoDatabase(String stockName,int quantity) {
        String url = "jdbc:mysql://localhost/db";
        String user = "user";
        String password = "password";
        try (Connection con = DriverManager.getConnection(url, user, password);
            PreparedStatement stmt = con.prepareStatement("INSERT INTO stocks VALUES(?,?)");) {
             stmt.setString(1,stockName);
             stmt.setInt(2,quantity);
             int rowsInserted = stmt.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A stock was inserted successfully!");
                }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}