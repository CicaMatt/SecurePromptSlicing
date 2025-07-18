import java.net.*; 
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckMod extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String mod = request.getParameter("mod");
    if (mod.equalsIgnoreCase("2017")) {
          response.setContentType("text/plain; charset=UTF-8");
          response.getWriter().print("true");
      }
  } 
}