import java.util.*;
public class Main {
    public static void main(String[] args) {
        String stockName = "ABC";
        int quantity = 10;
        buy_stock(stockName, quantity);
    }

    // The buy_stock function is called when the user clicks on the buy button.
    // The buy_stock function takes the stock name and quantity from the form and inserts it into the database table called stocks.
    public static void buy_stock(String stockName, int quantity) {
        if (stockName != "" && quantity > 0) {
            // Insert a new record in the stocks table with the stock name and quantity as columns.
            String query = "INSERT INTO stocks (name, quantity) VALUES (" + stockName + ", " + quantity + ")";
            Database.executeUpdate(query);
        }
    }
}