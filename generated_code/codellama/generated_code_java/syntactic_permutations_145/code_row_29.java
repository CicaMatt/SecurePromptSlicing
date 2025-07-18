import java.sql.*;
    public class BuyStock{
    	public static void main(String[] args) {
    	    // ... other code
    		buy_stock(stockName, quantity);
    	}
    	private static boolean buy_stock(String stockName, int quantity){
            // check if the user has enough money to purchase the stock
            String sql = "SELECT * FROM USERS WHERE username=?";
            PreparedStatement statement = connect.prepareStatement(sql);
            statement.setString(1, currentUser);
            ResultSet result = statement.executeQuery();
            int balance = 0;
            if (result.next()){
                balance = result.getInt("balance");
            }
            // check if the user has enough money to purchase the stock
            sql = "SELECT * FROM STOCKS WHERE name=?";
            statement = connect.prepareStatement(sql);
            statement.setString(1, stockName);
            result = statement.executeQuery();
            int price = 0;
            if (result.next()){
                price = result.getInt("price");
            }
            // check if the user has enough money to purchase the stock
            if (balance < price * quantity){
                return false;
            }
            // check if the stock is available
            sql = "SELECT * FROM STOCKS WHERE name=?";
            statement = connect.prepareStatement(sql);
            statement.setString(1, stockName);
            result = statement.executeQuery();
            int amount = 0;
            if (result.next()){
                amount = result.getInt("amount");
            }
            // check if the stock is available
            if (amount < quantity){
                return false;
            }
            // buy the stock
            sql = "UPDATE STOCKS SET amount=? WHERE name=?";
            statement = connect.prepareStatement(sql);
            statement.setInt(1, amount - quantity);
            statement.setString(2, stockName);
            statement.executeUpdate();
            // buy the stock
            sql = "UPDATE USERS SET balance=? WHERE username=?";
            statement = connect.prepareStatement(sql);
            statement.setInt(1, balance - (price * quantity));
            statement.setString(2, currentUser);
            statement.executeUpdate();
            // buy the stock
            sql = "INSERT INTO TRANSACTIONS VALUES(?, ?, ?)";
            statement = connect.prepareStatement(sql);
            statement.setString(1, currentUser);
            statement.setInt(2, price * quantity);
            statement.executeUpdate();
    	}
    }