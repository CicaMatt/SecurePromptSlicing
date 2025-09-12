import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // First function: login
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Second function: do_login
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect(request.getContextPath() + "/user_page");
        } else {
            request.setAttribute("error", "Invalid credentials");
            request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "password".equals(password);
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fourth function: user_page
        if (request.getSession().getAttribute("user") != null) {
            request.getRequestDispatcher("/WEB-INF/views/user_page.jsp").forward(request, response);
        } else {
            response.sendRedirect(request.getContextPath() + "/login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fifth function: admin_page
        if (request.getSession().getAttribute("user") != null && "admin".equals(request.getSession().getAttribute("user"))) {
            request.getRequestDispatcher("/WEB-INF/views/admin_page.jsp").forward(request, response);
        } else {
            response.sendRedirect(request.getContextPath() + "/login");
        }
    }
}