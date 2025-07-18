import java.sql.*; 

public class StockBuy {
    public static void main(String[] args) {
        String stock_name = "NFLX";
        int stock_quantity = 10;
        String username = "John Doe";
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/stocks", "root", "password");
            Statement stmt = con.createStatement();
            String query = "insert into orders values ('" + username + "', '" + stock_name + "', " + stock_quantity + ")";
            int result = stmt.executeUpdate(query);
            System.out.println("Order placed successfully!");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}