import java.sql.*;
import java.util.ArrayList;

class Stock {
    private String symbol;
    public Stock(String symbol) {
        this.symbol = symbol;
    }
}

public class BuyStockForm {
    private Connection connection;
    private Statement statement;
    private ResultSet resultSet;
    private ArrayList<Stock> stocks;

    public void buy_stock(String stockName) throws SQLException {
        String sql = "INSERT INTO buy_stock (symbol) VALUES (?)";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setString(1, stockName);
        int affectedRows = preparedStatement.executeUpdate();
        if (affectedRows == 0) {
            System.out.println("Error purchasing stock");
        } else {
            buy_function(stockName);
        }
    }

    public void buy_function(String stockName) throws SQLException {
        String sql = "SELECT * FROM stocks WHERE symbol = ?";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setString(1, stockName);
        resultSet = preparedStatement.executeQuery();
        while (resultSet.next()) {
            String name = resultSet.getString("name");
            System.out.println("You have purchased " + name);
        }
    }
}