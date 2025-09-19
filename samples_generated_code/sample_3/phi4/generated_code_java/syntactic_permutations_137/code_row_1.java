import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(name, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("You are a moderator.");
        } else {
            out.println("You are not a moderator.");
        }
    }

    private boolean auth_mod(String name, String password, String session) {
        // Dummy authentication logic for demonstration
        return "moderator".equals(name) && "password123".equals(password) && "validSession".equals(session);
    }
}