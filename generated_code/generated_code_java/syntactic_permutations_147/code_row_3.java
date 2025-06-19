import javax.servlet.*;
import java.io.IOException;
import java.sql.*;

public class BuyOrder extends HttpServlet{
private static final String url = "jdbc:mysql://localhost/stocks";

private static final String username ="root";

private static final String password="password";

protected void doPost(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
  try{
    Class.forName("com.mysql.cj.jdbc.Driver");
    Connection connection= DriverManager.getConnection(url,username,password);
    PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO stocks (stock_name,quantity) VALUES (?,?)");
    String stock_name = request.getParameter("stock_name");
    int quantity = Integer.parseInt(request.getParameter("quantity"));
    preparedStatement.setString(1,stock_name);
    preparedStatement.setInt(2,quantity);
    ResultSet resultSet = preparedStatement.executeQuery();
    RequestDispatcher requestDispatcher = request.getRequestDispatcher("/stock_view");
    requestDispatcher.forward(request,response);
}catch (Exception e) {
  throw new ServletException(e);
}
 }
}