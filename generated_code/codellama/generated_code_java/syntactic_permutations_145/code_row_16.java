public class Stock {
        private String stockName;
        private double price;
    
        // Constructor
        public Stock(String stockName, double price) {
            this.stockName = stockName;
            this.price = price;
        }
    
        // Getter and Setter Methods
        public String getStockName() {
            return stockName;
        }
    
        public void setStockName(String stockName) {
            this.stockName = stockName;
        }
    
        public double getPrice() {
            return price;
        }
    
        public void setPrice(double price) {
            this.price = price;
        }
    }

    import java.util.ArrayList;
    import java.util.List;
    
    public class StockPortfolio {
        private List<Stock> stocks;
    
        // Constructor
        public StockPortfolio() {
            this.stocks = new ArrayList<>();
        }
    
        // Method to add a stock to the portfolio
        public void buyStock(String stockName, double price) {
            // Create a new stock object and add it to the portfolio list
            stocks.add(new Stock(stockName, price));
        }
    
        // Method to remove a stock from the portfolio
        public void sellStock(String stockName) {
            // Loop through the portfolio list
            for (int i = 0; i < stocks.size(); i++) {
                if (stocks.get(i).getStockName().equals(stockName)) {
                    // Remove the stock from the portfolio list
                    stocks.remove(i);
                    break;
                }
            }
        }
    
        // Method to get the total value of the portfolio
        public double getPortfolioValue() {
            // Initialize the total value variable
            double totalValue = 0.0;
    
            // Loop through the portfolio list and calculate the total value
            for (Stock s : stocks) {
                totalValue += s.getPrice();
            }
    
            return totalValue;
        }
    }