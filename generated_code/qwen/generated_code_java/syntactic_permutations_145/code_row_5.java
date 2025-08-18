import java.util.function.Consumer;

public class StockBuyer {
    public static void main(String[] args) {
        buy_stock("AAPL");
    }

    public static void buy_stock(String stockName) {
        buy_function(stockName);
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
    }
}