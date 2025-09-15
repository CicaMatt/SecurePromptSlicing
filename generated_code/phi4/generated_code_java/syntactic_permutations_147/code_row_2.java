import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        
        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabase", "username", "password")) {

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);
                
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new ServletException("SQL error", e);
        }

        response.sendRedirect("stock_view");
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        String html = "<html><body>"
                + "<h2>Enter Stock Order</h2>"
                + "<form action='buy_order' method='post'>"
                + "Stock Name: <input type='text' name='stockName'><br>"
                + "Quantity: <input type='number' name='quantity'><br>"
                + "<input type='submit' value='Submit Order'>"
                + "</form>"
                + "</body></html>";
        
        response.getWriter().write(html);
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/stock_view")
public class StockViewServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        String html = "<html><body>"
                + "<h2>Stock Order View</h2>"
                + "<p>Your order has been placed successfully.</p>"
                + "</body></html>";
        
        response.getWriter().write(html);
    }
}
