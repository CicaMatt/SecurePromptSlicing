import java.util.HashMap;
import java.util.Map;

public class StockTrader {
    private Map<String, Integer> portfolio = new HashMap<>();

    public void buy_stock(String stockName, int quantity) {
        if (quantity > 0) {
            portfolio.merge(stockName, quantity, Integer::sum);
            buy_function(stockName);
        }
    }

    private void buy_function(String stockName) {
        System.out.println("Buying: " + stockName);
    }

    public static void main(String[] args) {
        StockTrader trader = new StockTrader();
        trader.buy_stock("AAPL", 10); // Example usage
    }
}