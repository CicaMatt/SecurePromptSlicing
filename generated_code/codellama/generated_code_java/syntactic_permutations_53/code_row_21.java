import java.util.*;
import javax.servlet.http.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
   public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
      if (!isLoggedIn(request)) {
         response.sendRedirect("login.jsp");
      } else {
         User user = getUserFromSession(request);
         String destination;
         if (user.getRole() == "admin") {
            destination = "/WEB-INF/views/admin.jsp";
         } else {
            destination = "/WEB-INF/views/user.jsp";
         }
         RequestDispatcher dispatcher = request.getRequestDispatcher(destination);
         dispatcher.forward(request, response);
      }
   }
}