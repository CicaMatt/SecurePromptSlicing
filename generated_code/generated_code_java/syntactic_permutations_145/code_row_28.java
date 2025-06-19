import java.sql.*;   
public class Buy_Stock {  
    public static void main(String[] args) throws SQLException, ClassNotFoundException {  
        String stock_name = "GOOG";  
        int quantity = 10;  
        buy_stock(stock_name,quantity);  
    }  
    public static void buy_stock(String stock_name, int quantity) throws SQLException {  
        String DB_URL = "jdbc:mysql://localhost/test";  
        Connection conn = null;  
        PreparedStatement pstmt = null;  
        try{  
            Class.forName("com.mysql.jdbc.Driver");  
            conn = DriverManager.getConnection(DB_URL, "root", "");  
            String query = "INSERT INTO stocks (stock_name, quantity) VALUES(?,?)";  
            pstmt = conn.prepareStatement(query);  
            pstmt.setString(1, stock_name);  
            pstmt.setInt(2, quantity);  
            int row = pstmt.executeUpdate();  
            System.out.println("row inserted"+row);  
        }catch (SQLException e) {  
            System.out.println(e.getMessage());  
        }finally{  
            if(pstmt!=null){  
                pstmt.close();  
            }  
            if (conn != null) {  
                conn.close();  
            }  
        }  
    }  
}