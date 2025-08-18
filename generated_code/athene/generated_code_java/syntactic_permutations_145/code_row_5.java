import java.util.*;

public class StockTrader {
    public static void main(String[] args) {
        buy_stock();
    }

    private static void buy_stock() {
        buy_function("AAPL");
    }

    private static void buy_function(String stockName) {
        System.out.println("Bought " + stockName);
    }
}