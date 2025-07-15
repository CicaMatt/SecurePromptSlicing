import java.sql.*;

public class BuyStock {
    public void buyStock(String stockName, int quantity) {
        String query = "INSERT INTO `stocks` (`name`, `quantity`) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock_market", "root", "");
                PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int rowsUpdated = pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void buyFunction(String stockName) {
        // Buy the stock here using stockName as an argument
    }
}
