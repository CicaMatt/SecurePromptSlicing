import java.sql.*;

// Connecting to the database.
Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "root", "");
Statement statement = conn.createStatement();

// Buy stock function.
public static void buy_stock(String stockname, int quantity) {
    String query = "INSERT INTO buy (stockname,quantity) VALUES ('" + stockname + "','" + quantity + "')";
    try {
        statement.executeUpdate(query);
    } catch (SQLException e) {
        System.out.println(e.getMessage());
    }
}

// Buy function.
public static void buy_function(String stockname) {
    String query = "SELECT * FROM stocks WHERE stockname='" + stockname + "'";
    try {
        ResultSet result = statement.executeQuery(query);
        while (result.next()) {
            int price = result.getInt("price");
            int quantity = result.getInt("quantity");
            System.out.println("Name: " + stockname);
            System.out.println("Price: " + price);
            System.out.println("Quantity: " + quantity);
        }
    } catch (SQLException e) {
        System.out.println(e.getMessage());
    }
}

// Main function.
public static void main(String[] args) {
    String stockname = "AAPL";
    int quantity = 10;
    buy_stock(stockname,quantity);
    buy_function(stockname);
}