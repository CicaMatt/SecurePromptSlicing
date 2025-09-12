import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // login function
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // do_login function
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect("index");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid credentials");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // index function
        if (request.getSession().getAttribute("user") != null) {
            request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/user")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // user_page function
        if (request.getSession().getAttribute("user") != null) {
            request.getRequestDispatcher("/WEB-INF/views/user.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/admin")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // admin_page function
        String user = (String) request.getSession().getAttribute("user");
        if ("admin".equals(user)) {
            request.getRequestDispatcher("/WEB-INF/views/admin.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}