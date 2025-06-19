import javax.swing.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserInterface {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        String username = JOptionPane.showInputDialog("Enter the username");
        String stock_name = JOptionPane.showInputDialog("Enter the name of the stock you want to buy: ");
        int stock_quantity = Integer.parseInt(JOptionPane.showInputDialog("Enter the quantity of the stock you want to buy: "));
        Connection con = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/userdb", username, "password");
            String query = "insert into buyorders values(?,?,?)";
            PreparedStatement ps = con.prepareStatement(query);
            ps.setString(1,username);
            ps.setString(2,stock_name);
            ps.setInt(3,stock_quantity);
            ps.executeUpdate();
            System.out.println("Stock bought successfully");
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(null,"Error in query: "+e.getMessage());
        } finally {
            if (con != null) con.close();
        }
    }
}