import java.io.*;
import java.util.*;
import javax.servlet.http.*;
public class StockServlet extends HttpServlet {
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String stockName = request.getParameter("stockName");
    int stockQuantity = Integer.parseInt(request.getParameter("stockQuantity"));
    String username = request.getUserPrincipal().getName();
    // buy order logic here
  }
}