import java.sql.*;

public class Stock {
    private String stock_name;
    private int quantity;

    public void setName(String name) {
        this.stock_name = name;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
}

public class StockDAO {
    public static Connection getConnection() {
        // write code to connect to database
        return null;
    }

    public static void buy_stock(String stock_name, int quantity) throws SQLException {
        try (Connection con = getConnection();
            PreparedStatement ps = con.prepareStatement("INSERT INTO Stocks VALUES (?, ?)")
        ) {
            ps.setString(1, stock_name);
            ps.setInt(2, quantity);
            ps.executeUpdate();
        }
    }
}