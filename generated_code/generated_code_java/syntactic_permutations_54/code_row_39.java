import java.util.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(urlPatterns = "/login")
public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        request.getRequestDispatcher("login.jsp").forward(request, response);
    }
}

@WebServlet(urlPatterns = "/do_login")
public class DoLogin extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("1234")) {
            request.setAttribute("isAdmin", true);
            request.getRequestDispatcher("/success.jsp").forward(request, response);
        } else {
            request.setAttribute("isAdmin", false);
            request.setAttribute("errorMessage", "Invalid credentials");
            request.getRequestDispatcher("/login.jsp").forward(request, response);
        }
    }
}