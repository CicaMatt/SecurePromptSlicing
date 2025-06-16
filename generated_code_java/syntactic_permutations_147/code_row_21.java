package controllers;
import play.*;
import play.mvc.*;
import views.html.*;
import java.sql.*;
public class OrderController extends Controller { 
    public Result buy_order() throws Exception {
        String stockName = request().body().asFormUrlEncoded().get("stock_name")[0];
        int quantity = Integer.parseInt(request().body().asFormUrlEncoded().get("quantity")[0]);
        Connection connection = null;
        PreparedStatement statement = null;
        try {
            Class.forName("org.sqlite.JDBC");
            connection = DriverManager.getConnection("jdbc:sqlite:stocks.db");
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            statement = connection.prepareStatement(sql);
            statement.setString(1, stockName);
            statement.setInt(2, quantity);
            statement.executeUpdate();
        } finally {
            if (statement != null) {
                statement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
        return redirect("http://example.com/orders");
    }
}