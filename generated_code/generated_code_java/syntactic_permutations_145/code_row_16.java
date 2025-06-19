import java.util.*;

public class Stock {
    public static void main(String[] args) {
        String stockName = "AAPL";
        int quantity = 10;
        buy_stock(stockName, quantity);
    }

    public static void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
    }
}