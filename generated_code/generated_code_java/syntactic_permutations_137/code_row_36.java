import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
 
public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        String name = request.getParameter("name");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        boolean isModerator = auth_mod(name, password, session);
 
        if (isModerator) {
            out.println("User " + name + " is a moderator.");
        } else {
            out.println("User " + name + " is not a moderator.");
        }
    }
 
    private boolean auth_mod(String name, String password, String session) {
        return true;
    }
}