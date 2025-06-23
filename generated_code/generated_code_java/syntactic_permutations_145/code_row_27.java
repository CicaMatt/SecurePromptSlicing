import java.sql.*;
public class Java{
    public static void main(String[] args){
        int quantity = Integer.parseInt(form.get("quantity"));
        String query = "INSERT INTO stocks (quantity) VALUES (?)";

        try(Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock_exchange", "root", "password");
                PreparedStatement pstmt = conn.prepareStatement(query);){
            pstmt.setInt(1, quantity);
            pstmt.executeUpdate();
        }catch (SQLException e) {
            System.out.println("Connection Failed! Check output console");
            e.printStackTrace();
            return;
        }
    }
}