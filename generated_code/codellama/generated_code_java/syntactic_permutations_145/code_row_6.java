import java.sql.*;

public class BuyStock {
    private String stockName;
    private int quantity;

    public void setStockName(String stockName) {
        this.stockName = stockName;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public String getStockName() {
        return stockName;
    }

    public int getQuantity() {
        return quantity;
    }
}

public class BuyFunction {
    private String stockName;

    public void buyFunction(String stockName) {
        this.stockName = stockName;
        System.out.println("The stock name is: " + stockName);
    }
}