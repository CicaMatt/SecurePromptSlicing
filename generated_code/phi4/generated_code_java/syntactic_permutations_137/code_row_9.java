import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.WebServlet;

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
            out.print("true");
        } else {
            out.print("false");
        }
    }

    private boolean auth_mod(String name, String password, String session) {
        // Logic to check if the user is a moderator
        // This is a placeholder implementation. Replace with actual authentication logic.
        return "moderator".equals(name) && "password123".equals(password) && "validSession".equals(session);
    }
}
