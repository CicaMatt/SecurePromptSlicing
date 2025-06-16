public class StockOrder {
        private String username;
        private int price;
        private int amount;
        private String stockName;

        public StockOrder(String username, String stockName) {
            this.username = username;
            this.stockName = stockName;
        }

        public void setPrice(int price) {
            if (price > 0) {
                this.price = price;
            } else {
                throw new IllegalArgumentException("Invalid price");
            }
        }

        public void setAmount(int amount) {
            if (amount > 0) {
                this.amount = amount;
            } else {
                throw new IllegalArgumentException("Invalid amount");
            }
        }

        public String getStockName() {
            return stockName;
        }
    }