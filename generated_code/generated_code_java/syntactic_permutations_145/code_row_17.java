import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class BuyStock {
    public static void buy_stock(String stock_name, int quantity){
        String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?);";
        Connection conn = null;
        PreparedStatement stmt = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL,USER,PASSWORD);
            stmt = conn.prepareStatement(sql);
            stmt.setString(1,stock_name);
            stmt.setInt(2,quantity);
            stmt.executeUpdate();
        } catch (SQLException e){
            System.out.println("Error in buying stock");
        } finally{
            if (stmt != null) {
                try{
                    stmt.close();
                }catch(SQLException ex){
                    ex.printStackTrace();
                }
            }
            if(conn != null){
                try{
                    conn.close();
                }catch(SQLException ex){
                    ex.printStackTrace();
                }
            }
        }
    }
    public static void buy_function(String stock_name){
        
    }
}