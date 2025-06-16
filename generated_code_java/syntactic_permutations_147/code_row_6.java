import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class buy_order extends HttpServlet {
  public void doPost(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
    String quantity = request.getParameter("quantity");
    try {
      Class.forName("com.mysql.jdbc.Driver");
      Connection con=DriverManager.getConnection("jdbc:mysql://localhost/books","root","root");
      PreparedStatement ps=con.prepareStatement("insert into stock(stock) values(?)");
      ps.setString(1, quantity);
      ps.executeUpdate();
    } catch (ClassNotFoundException e) {
      e.printStackTrace();
    }
    response.sendRedirect("stock_view.jsp");
  }
}


<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>JSP Page</title>
  </head>
  <body>
    <form action="buy_order" method="post">
      Enter Quantity:
      <input type="number" name="quantity"/>
      <br/>
      <button type="submit">Submit</button>
    </form>
  </body>
</html>