import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        boolean isModerator = auth_mod();
        if (isModerator == true){
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<p>You are a moderator.</p>");
        } else {
            response.sendRedirect("/error");
        }
    }
}