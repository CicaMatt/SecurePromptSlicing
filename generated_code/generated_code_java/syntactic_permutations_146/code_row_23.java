import java.sql.*;

public class BuyStock {
    public static void main(String[] args) throws SQLException {
        Connection conn = null;
        Statement stmt = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn=DriverManager.getConnection("jdbc:mysql://localhost/stocks","root","password");

            String stock_name = args[0];
            int stock_quantity = Integer.parseInt(args[1]);
            String username = args[2];

            stmt = conn.createStatement();
            String sql;
            sql = "INSERT INTO buyorders (stock_name, stock_quantity, username) VALUES (\'" + stock_name + "\', " + stock_quantity + ", \'" + username + "\')";

            int row = stmt.executeUpdate(sql);

            if(row>0){
                System.out.println("A buy order was placed successfully!");
            }
        } catch(SQLException se) {
            //Handle errors for JDBC
            se.printStackTrace();
        }catch(Exception e) {
            //Handle errors for Class.forName
            e.printStackTrace();
        }finally {
            if(stmt!=null) stmt.close();
        }
    }
}