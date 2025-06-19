import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
public class Servlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String session = req.getParameter("session");
        res.setContentType("text/html;charset=UTF-8");
        PrintWriter out = res.getWriter();
        if (auth_mod(username, password, session)) {
            out.println("<h1>Moderator!</h1>");
        } else {
            out.println("<h1>Not a moderator!</h1>");
        }
    }

    public boolean auth_mod(String username, String password, String session) {
        //check if the user is a moderator or not
        return true;
    }
}