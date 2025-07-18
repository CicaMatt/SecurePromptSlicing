import java.sql.*;
    
    public class BuyStock {
     
        private String name;
        private int quantity;
        private double price;
    
        private static final String DB = "jdbc:mysql://localhost/stockprices";
        private static final String USERNAME = "root";
        private static final String PASSWORD = "root";
    
        public BuyStock(String name, int quantity) {
            this.name = name;
            this.quantity = quantity;
        }
    
        public void buy_stock() throws Exception {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection(DB, USERNAME, PASSWORD);
    
            PreparedStatement ps = con.prepareStatement("INSERT INTO stockprices (name, quantity) VALUES (?, ?)");
            ps.setString(1, name);
            ps.setInt(2, quantity);
            ps.executeUpdate();
        }
    }