import java.sql.*;
    
    public class StockTransaction {
        private String stockName;
        private double quantity;
        
        public void setStock(String name) {
            this.stockName = name;
        }
        
        public String getStock() {
            return this.stockName;
        }
        
        public void setQuantity(double quantity) {
            this.quantity = quantity;
        }
        
        public double getQuantity() {
            return this.quantity;
        }
    
    }