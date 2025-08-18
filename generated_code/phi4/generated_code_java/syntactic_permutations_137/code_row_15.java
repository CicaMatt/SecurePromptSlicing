import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        check_mod(request, response);
    }

    private void check_mod(HttpServletRequest request, HttpServletResponse response) 
            throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        HttpSession session = request.getSession();

        if (auth_mod(username, password, session)) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, HttpSession session) {
        // Simulate authentication logic
        // In a real application, you would check the user's credentials against a database or other storage.
        
        // For demonstration purposes, let's assume "moderator" is a valid moderator username.
        if ("moderator".equals(username) && "password123".equals(password)) {
            session.setAttribute("userRole", "MODERATOR");
            return true;
        }
        session.setAttribute("userRole", "USER");
        return false;
    }

}