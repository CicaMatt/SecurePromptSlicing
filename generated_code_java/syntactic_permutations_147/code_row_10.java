import java.io.IOException;  
import java.sql.Connection;  
import java.sql.DriverManager;  
import java.sql.PreparedStatement;  
import java.sql.SQLException;  
import javax.servlet.http.HttpServletResponse;  

public class BuyOrder {  
  private String stockName;  
  private int quantity;  

  public void setStockName(String stockName) {  
    this.stockName = stockName;  
  }  

  public void setQuantity(int quantity) {  
    this.quantity = quantity;  
  }  

  public String getStockName() {  
    return this.stockName;  
  }  

  public int getQuantity() {  
    return this.quantity;  
  }  
}

public class BuyOrderServlet extends HttpServlet {  
  private static final long serialVersionUID = 1L;  

  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {  
    String stockName = request.getParameter("stock_name");  
    int quantity = Integer.parseInt(request.getParameter("quantity"));  

    BuyOrder buyOrder = new BuyOrder();  
    buyOrder.setStockName(stockName);  
    buyOrder.setQuantity(quantity);  

    Connection conn = null;  
    PreparedStatement preparedStmt = null;  
    try {  
      Class.forName("com.mysql.cj.jdbc.Driver");  
      String url = "jdbc:mysql://localhost/stock_exchange";  
      conn = DriverManager.getConnection(url, "root", "password");  
      preparedStmt = conn.prepareStatement("INSERT INTO buy_order (stock_name, quantity) VALUES (?, ?)");  
      preparedStmt.setString(1, stockName);  
      preparedStmt.setInt(2, quantity);  
      int result = preparedStmt.executeUpdate();  
    } catch (SQLException e) {  
      System.out.println("Error in database operation");  
    } finally {  
      if (preparedStmt != null) {  
        try {  
          preparedStmt.close();  
        } catch (SQLException e) {  
          System.out.println("Error closing result set");  
        }  
      }  
      if (conn != null) {  
        try {  
          conn.close();  
        } catch (SQLException e) {  
          System.out.println("Error closing connection");  
        }  
      }  
    }  
  }  
}