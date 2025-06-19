import java.sql.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(urlPatterns = {"/buy_order"})
public class BuyOrder extends HttpServlet {
  private String dbUrl = "jdbc:postgresql://localhost:5432/stock_exchange";
  private Connection connection;
  
  @Override
  public void init() throws ServletException {
    try {
      Class.forName("org.postgresql.Driver");
      connection = DriverManager.getConnection(dbUrl);
    } catch (ClassNotFoundException | SQLException e) {
        throw new ServletException(e);
    }
  }
  
  @Override
  public void destroy() {
    try {
      if (!connection.isClosed()) {
        connection.close();
      }
    } catch (SQLException e) {
        e.printStackTrace();
    }
  }
  
  @Override
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String stockName = request.getParameter("stock_name");
    int quantity = Integer.parseInt(request.getParameter("quantity"));
    
    try {
      PreparedStatement statement = connection.prepareStatement("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)");
      statement.setString(1, stockName);
      statement.setInt(2, quantity);
      
      int rowsInserted = statement.executeUpdate();
      if (rowsInserted > 0) {
        response.sendRedirect("/stock_view?message=Stock%20purchase%20successful");
      } else {
        response.sendRedirect("/stock_view?error=Stock%20purchase%20failed");
      }
    } catch (SQLException e) {
        throw new ServletException(e);
    }
  }
}