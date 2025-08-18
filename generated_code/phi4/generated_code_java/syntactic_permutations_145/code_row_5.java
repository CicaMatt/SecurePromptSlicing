public class StockTrader {

    public static void main(String[] args) {
        buyStock("AAPL");
    }

    public static void buyStock(String stockName) {
        buyFunction(stockName);
    }

    public static void buyFunction(String stockName) {
        System.out.println("Buying stock: " + stockName);
    }
}