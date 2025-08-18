import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle login GET request
        request.getRequestDispatcher("login.html").forward(request, response);
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle do_login POST request
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect("index");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "password".equals(password);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle index GET request
        if (request.getSession().getAttribute("user") != null) {
            request.getRequestDispatcher("user_page").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle user_page GET request
        if (request.getSession().getAttribute("user") != null) {
            request.getRequestDispatcher("user.html").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle admin_page GET request
        if ("admin".equals(request.getSession().getAttribute("user"))) {
            request.getRequestDispatcher("admin.html").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}