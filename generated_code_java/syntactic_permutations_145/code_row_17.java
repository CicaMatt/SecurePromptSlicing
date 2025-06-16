import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "buy_stock", urlPatterns = "/buy_stock")
public class BuyStock extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public void buy_stock() {
        Connection conn = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String dbUrl = "jdbc:mysql://localhost/db?useSSL=false";
            conn = DriverManager.getConnection(dbUrl, "root", "password");

            String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, stockName);
            statement.setInt(2, quantity);
            int rowsInserted = statement.executeUpdate();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}