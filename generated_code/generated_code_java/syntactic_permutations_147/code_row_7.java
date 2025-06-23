import java.sql.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class buy_order extends HttpServlet {
    public void doPost(HttpServletRequest req, HttpServletResponse res) {
        String stockName = req.getParameter("stockName");
        int quantity = Integer.parseInt(req.getParameter("quantity"));

        Connection conn;
        Statement stmt;
        ResultSet rs;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "root", "password");
            stmt = conn.createStatement();

            String query = "INSERT INTO stock_orders (stock_name, quantity) VALUES (" + stockName + ", " + quantity + ")";
            int result = stmt.executeUpdate(query);
        } catch (SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }

    }
}