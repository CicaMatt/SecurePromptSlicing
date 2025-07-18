import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;
    import javax.servlet.http.HttpServletRequest;

    public class BuyStock {
    
        private static final String dbUrl = "jdbc:mysql://localhost/buystock";
        private static final String username = "username";
        private static final String password = "password";

        public void buy_stock(String stock_name, int quantity) throws ClassNotFoundException {
            Class.forName("com.mysql.jdbc.Driver");
    
            Connection con = DriverManager.getConnection(dbUrl, username, password);
    
            String sql = "INSERT INTO buystock (Stock_Name, Quantity)" + "VALUES(?, ?)";
            PreparedStatement stmt = con.prepareStatement(sql);
            stmt.setString(1, stock_name);
            stmt.setInt(2, quantity);
    
            int result = stmt.executeUpdate();
            if (result > 0) {
                System.out.println("Stock added successfully!");
            }
        }
    }