import java.sql.*;

public class Stock {
    public static void main(String[] args) {
        String stock_name = "";
        int quantity = 0;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/wallet", "root", "root");
            PreparedStatement ps = con.prepareStatement("insert into stock values(?,?)");
            ps.setString(1, stock_name);
            ps.setInt(2, quantity);
            int i = ps.executeUpdate();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}