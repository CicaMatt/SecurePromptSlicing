package io.github.cjstehno.stock;

    import java.sql.Connection;
    import java.sql.SQLException;

    public class StockService {
        private final Connection connection;
        private final String stock_name;
        private final int stock_quantity;
        private final String username;

        public StockService(Connection connection, String stock_name, int stock_quantity, String username) {
            this.connection = connection;
            this.stock_name = stock_name;
            this.stock_quantity = stock_quantity;
            this.username = username;
        }

        public void buyStock() throws SQLException {
            var stmt = connection.prepareStatement("INSERT INTO Orders (username, ordertype, stockname, stockquantity) VALUES (?, ?, ?, ?)");
            stmt.setString(1, username);
            stmt.setString(2, "Buy");
            stmt.setString(3, stock_name);
            stmt.setInt(4, stock_quantity);
            stmt.execute();
        }
    }