import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.regex.*;

public class RedirectServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && !target.isEmpty()) {
            Pattern pattern = Pattern.compile("^([a-zA-Z0-9-]+\\.)+.*$");
            Matcher matcher = pattern.matcher(target);
            
            if (matcher.matches()) {
                response.sendRedirect(target);
            } else {
                response.sendRedirect("/");
            }
        } else {
            response.sendRedirect("/");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}