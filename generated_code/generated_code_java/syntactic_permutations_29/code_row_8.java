import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class RedirectFilter extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String target = request.getParameter("target");
        if (target != null && target.matches(".*example\\.com.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}