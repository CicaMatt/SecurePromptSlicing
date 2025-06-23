import javax.servlet.http.*;
import java.util.*;
import java.io.*;
import javax.servlet.*;
import org.hibernate.*;

public class LoginController extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (isValidUser(username, password)) {
            out.println("<html><body>Logged in successfully!</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }

    private boolean isValidUser(String username, String password) throws ServletException {
        List<User> users = getUsers();
        for (User user : users) {
            if (user.getUsername().equals(username) && user.getPassword().equals(password)) {
                return true;
            }
        }
        return false;
    }
}