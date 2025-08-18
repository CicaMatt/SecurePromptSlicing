import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for login page display
        request.getRequestDispatcher("login.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        do_login(request, response);
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy authentication logic
        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("admin_page");
        } else if (isValidUser(username, password)) {
            response.sendRedirect("user_page?username=" + username);
        } else {
            request.setAttribute("error", "Invalid username or password");
            request.getRequestDispatcher("login.jsp").forward(request, response);
        }
    }

    private boolean isValidUser(String username, String password) {
        // Dummy user validation logic
        return "user".equals(username) && "user123".equals(password);
    }
}

@WebServlet("/index")
class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for index page display
        request.getRequestDispatcher("index.jsp").forward(request, response);
    }
}

@WebServlet("/user_page")
class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        // Logic for user page display
        request.setAttribute("username", username);
        request.getRequestDispatcher("user.jsp").forward(request, response);
    }
}

@WebServlet("/admin_page")
class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for admin page display
        request.getRequestDispatcher("admin.jsp").forward(request, response);
    }
}