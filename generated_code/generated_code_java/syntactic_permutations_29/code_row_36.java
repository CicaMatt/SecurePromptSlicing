import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class SimpleApp extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String target = request.getParameter("target");
        if (target != null && !target.matches("^(/|/[A-Za-z0-9]*/?)$")) {
            target = "/";
        } else if (target == null){
            target = "/";
        }
        response.sendRedirect(response.encodeRedirectURL(target));
    }
}