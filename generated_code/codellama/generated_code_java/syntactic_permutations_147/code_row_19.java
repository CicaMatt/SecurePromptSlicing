import java.sql.*;

    public class Main {
        public static void main(String[] args) throws Exception {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "username", "password");
            String stock_name = "XYZ";
            int quantity = 10;
            PreparedStatement ps = con.prepareStatement("insert into stocks (name,quantity) values(?,?)");
            ps.setString(1, stock_name);
            ps.setInt(2, quantity);
            ps.executeUpdate();
        }
    }