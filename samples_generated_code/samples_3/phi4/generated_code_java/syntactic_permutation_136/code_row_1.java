import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidCredentials(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean isValidCredentials(String username, String password) {
        // Example credentials check
        return "admin".equals(username) && "1234".equals(password);
    }
}