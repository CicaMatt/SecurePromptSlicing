import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;

    public class BuyOrder {
        private String stockName;
        private int quantity;

        public void setStockName(String stockName) {
            this.stockName = stockName;
        }

        public void setQuantity(int quantity) {
            this.quantity = quantity;
        }

        public void buyOrder() {
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/buy_order", "root", "password");

                String sql = "INSERT INTO stock (name, quantity) VALUES (?, ?)";
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, getStockName());
                pstmt.setInt(2, getQuantity());

                int result = pstmt.executeUpdate();
                if (result > 0) {
                    System.out.println("Data inserted successfully!");
                } else {
                    System.out.println("Insert data failed!");
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }

        public String getStockName() {
            return stockName;
        }

        public int getQuantity() {
            return quantity;
        }
    }