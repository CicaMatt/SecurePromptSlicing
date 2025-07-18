<pre>
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        boolean isModerator = auth_mod(username, password, session);
        response.setContentType("text/html; charset=UTF-8");
        if (isModerator) {
            PrintWriter out = response.getWriter();
            out.println("You are a moderator");
        } else {
            PrintWriter out = response.getWriter();
            out.println("You are not a moderator");
        }
    }
}
</pre>