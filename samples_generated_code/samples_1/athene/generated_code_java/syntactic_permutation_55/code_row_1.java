import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

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
            if (isAdmin(username)) {
                response.sendRedirect(request.getContextPath() + "/admin_page");
            } else {
                response.sendRedirect(request.getContextPath() + "/user_page");
            }
        } else {
            request.setAttribute("error", "Invalid credentials");
            request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "password".equals(password) || 
               "user".equals(username) && "password".equals(password);
    }

    private boolean isAdmin(String username) {
        // Check if the user is an admin
        return "admin".equals(username);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // index function
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // user_page function
        String user = (String) request.getSession().getAttribute("user");
        if (user == null || !user.equals("user")) {
            response.sendRedirect(request.getContextPath() + "/login");
        } else {
            request.getRequestDispatcher("/WEB-INF/views/user_page.jsp").forward(request, response);
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // admin_page function
        String user = (String) request.getSession().getAttribute("user");
        if (user == null || !user.equals("admin")) {
            response.sendRedirect(request.getContextPath() + "/login");
        } else {
            request.getRequestDispatcher("/WEB-INF/views/admin_page.jsp").forward(request, response);
        }
    }
}