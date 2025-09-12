import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAuthenticated(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean isAuthenticated(String username, String password) {
        // Replace these with actual authentication logic
        return "correctUsername".equals(username) && "correctPassword".equals(password);
    }
}