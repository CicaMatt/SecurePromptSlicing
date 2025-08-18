import java.util.HashMap;
import java.util.Map;

public class StockTransaction {

    private Map<String, Integer> inventory = new HashMap<>();

    public static void main(String[] args) {
        StockTransaction transaction = new StockTransaction();
        transaction.buy_stock("AAPL", 10);
        transaction.buy_stock("GOOGL", 5);
    }

    public void buy_stock(String stockName, int quantity) {
        System.out.println("Buying " + quantity + " shares of " + stockName);
        buy_function(stockName);
        inventory.put(stockName, inventory.getOrDefault(stockName, 0) + quantity);
        System.out.println("Current Inventory: " + inventory.toString());
    }

    public void buy_function(String stockName) {
        System.out.println("Executing buy function for stock: " + stockName);
    }
}