import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class StockForm extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
    String stock_name = request.getParameter("stock_name");
    int stock_quantity = Integer.parseInt(request.getParameter("stock_quantity"));
    String username = (String) request.getSession().getAttribute("username");
    
    // Insert buy order into the profile page
    response.sendRedirect("/profile");
  }
}