import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "CheckModServlet", urlPatterns = {"/check_mod"})
public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidUser(username, password)) {
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.getWriter().write("false");
        }
    }

    private boolean isValidUser(String username, String password) {
        // Replace these with actual validation logic
        return "admin".equals(username) && "password123".equals(password);
    }
}
