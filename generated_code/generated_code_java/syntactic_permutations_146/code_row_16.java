import java.sql.*;
public class Main{
    public static void main(String[] args) {
        String stockName = "ABC";
        int stockQuantity = 100; 
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb", "root", "rootpassword");
            PreparedStatement preparedStatement = con.prepareStatement("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)");
            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, stockQuantity); 
            int result = preparedStatement.executeUpdate();
        } catch (Exception e) {
            System.out.println(e);
        }
    } 
}