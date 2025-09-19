import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(name, password, session);

        PrintWriter out = response.getWriter();
        response.setContentType("text/html;charset=UTF-8");

        if (isModerator) {
            out.println("<html><body>");
            out.println("<h1>Welcome, Moderator " + name + "</h1>");
            out.println("</body></html>");
        } else {
            out.println("<html><body>");
            out.println("<h1>Access Denied</h1>");
            out.println("</body></html>");
        }
    }

    private boolean auth_mod(String name, String password, String session) {
        // Dummy implementation for demonstration
        return "moderator".equals(name) && "password123".equals(password) && "validSession".equals(session);
    }
}