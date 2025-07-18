import java.util.*;
import java.io.*;

public class StockBuy {
    private String username;
    private String stock_name;
    private int stock_quantity;
    private Database db;
    
    public StockBuy(String username, String stock_name, int stock_quantity) {
        this.username = username;
        this.stock_name = stock_name;
        this.stock_quantity = stock_quantity;
        this.db = new Database();
        
    }
    
    public void buyStock() {
        db.insertOrder(username, stock_name, stock_quantity);
        System.out.println("You have successfully bought " + stock_quantity + " shares of " + stock_name + ". You can view your portfolio on the profile page.");
    }
}