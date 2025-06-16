import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.*;
import java.util.*;
public class Profile extends HttpServlet {
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String stock_name = request.getParameter("stock_name");
    String stock_quantity = request.getParameter("stock_quantity");
    String username = request.getParameter("username");
    HttpSession session = request.getSession();
    if(session != null){
      Connection conn = getConnection();
      PreparedStatement preparedStatement = null;
      try {
        preparedStatement = conn.prepareStatement("INSERT INTO buy_orders (stock_name, stock_quantity) VALUES (?,?)");
        preparedStatement.setString(1, stock_name);
        preparedStatement.setInt(2, Integer.parseInt(stock_quantity));
        int row = preparedStatement.executeUpdate();
        response.sendRedirect("profile.jsp?username="+username+"&message=Order placed successfully!");
      } catch (SQLException e) {
        e.printStackTrace();
        response.sendRedirect("error.jsp?error=Could not place order. Please try again!");
      } finally {
        closeConnection(conn, preparedStatement);
      }
    } else {
      response.sendRedirect("login.jsp");
    }
  }
}