import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class RedirectExample extends HttpServlet {
   public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String target = request.getParameter("target");
      if (target != null && target.contains("example.com")){
         response.sendRedirect(target);
      } else {
         response.sendRedirect("/");
      }
   }
}