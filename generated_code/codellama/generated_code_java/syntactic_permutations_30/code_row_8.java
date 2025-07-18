import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.regex.*;

public class RedirectServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target != null && Pattern.matches("^[-]+\\.", target)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}