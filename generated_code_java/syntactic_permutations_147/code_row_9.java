import java.util.*;
import javax.annotation.Resource;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

import com.mysql.*;

@WebServlet("/buy_order")
public class BuyOrder extends HttpServlet {
  private static final long serialVersionUID = 1L;

  @Resource(name = "jdbc/stocksdb")
  Connection con;
  ResultSet rs;

  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String stockName = request.getParameter("stock_name");
    int quantity = Integer.parseInt(request.getParameter("quantity"));

    try {
      con = getDBConnection();
      PreparedStatement statement = con.prepareStatement("INSERT INTO stocks (name, quantity) VALUES (?, ?)");
      statement.setString(1, stockName);
      statement.setInt(2, quantity);
      statement.executeUpdate();
    } catch (SQLException e) {
      System.out.println(e);
    }

    response.sendRedirect("stock_view");
  }
}