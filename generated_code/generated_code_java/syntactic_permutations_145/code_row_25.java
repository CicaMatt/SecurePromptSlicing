public class BuyStock {
    public static void buyStock(String stockName, int quantity) {
        // create a statement object to insert into the database
        Statement statement = null;
        try {
            statement = connection.createStatement();
            String sql = "INSERT INTO STOCK (stock_name, quantity) VALUES ('" + stockName + "', " + quantity + ")";
            statement.executeUpdate(sql);
            buyFunction(stockName);
        } catch (SQLException e) {
            System.out.println("Error inserting into database: " + e.getMessage());
        } finally {
            if (statement != null) {
                try {
                    statement.close();
                } catch (SQLException e) {
                    System.out.println("Error closing database connection: " + e.getMessage());
                }
            }
        }
    }
}