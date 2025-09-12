import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // login function
        request.getRequestDispatcher("login.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // do_login function
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            request.getSession().setAttribute("user", username);
            if (isUserAdmin(username)) {
                response.sendRedirect("admin_page");
            } else {
                response.sendRedirect("user_page");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid credentials");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "admin123".equals(password);
    }

    private boolean isUserAdmin(String username) {
        // Check if user is admin
        return "admin".equals(username);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // index function
        request.getRequestDispatcher("index.jsp").forward(request, response);
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // user_page function
        if (request.getSession().getAttribute("user") != null) {
            request.getRequestDispatcher("user_page.jsp").forward(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Not logged in");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // admin_page function
        if (request.getSession().getAttribute("user") != null && isUserAdmin(request.getSession().getAttribute("user").toString())) {
            request.getRequestDispatcher("admin_page.jsp").forward(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Not authorized to access this page");
        }
    }

    private boolean isUserAdmin(String username) {
        // Check if user is admin
        return "admin".equals(username);
    }
}