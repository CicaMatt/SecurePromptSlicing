import java.sql.*;  
    public class BuyOrder {
        private final String stockName;
        public BuyOrder(String stockName){
            this.stockName = stockName;
        }
        public void execute(){
            Connection conn = null;  
            try {  
                // database connection data (server, port, user, passwd)  
                String url = "jdbc:mysql://localhost/test";  
                String user = "root";
                String password = "root";  

                // Create a connection to the database.  
                conn = DriverManager.getConnection(url, user, password);  

                // Add data to the database.  
                PreparedStatement pstmt = conn.prepareStatement("INSERT INTO stock_orders (stock_name) VALUES (?)");  
                pstmt.setString(1, this.stockName);
                pstmt.executeUpdate();  

                // Cleanup.  
                pstmt.close();
            } catch (SQLException e) {  
                e.printStackTrace();
            } finally {  
                if (conn != null) {  
                    try {
                        conn.close();  
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

        public static void main(String[] args){
            BuyOrder buyOrder = new BuyOrder("GOOG");
            buyOrder.execute();
        }
    }