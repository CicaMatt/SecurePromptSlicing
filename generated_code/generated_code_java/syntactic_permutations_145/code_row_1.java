import java.sql.*;

public class Stock {
    
    public static void buy_stock(String stock, int quantity) {  // called when user clicks on buy button
        // Insert into database
        
        buy_function(stock);  // call buy_function function and pass the stock as an argument
    }
    
    public static void buy_function(String stock) {
        // Buy the stock
        System.out.println("Buying " + quantity + " shares of " + stock);
    }
}