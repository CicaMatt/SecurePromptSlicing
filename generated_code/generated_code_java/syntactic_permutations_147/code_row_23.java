import java.sql.*;
public class Order{
    private String stockName;
    private int quantity;
    public Order(String stockName,int quantity){
        this.stockName=stockName;
        this.quantity=quantity;
    }
    public void buy_order(){
        try {
            //insert into database
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase","username","password");
            String query="INSERT INTO `orders`(`stockName`,`quantity`) VALUES (?,?)";
            PreparedStatement stmt=con.prepareStatement(query);
            stmt.setString(1,this.stockName);
            stmt.setInt(2,this.quantity);
            int rowsInserted = stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}