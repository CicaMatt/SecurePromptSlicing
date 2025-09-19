import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login function
        request.getRequestDispatcher("login.jsp").forward(request, response);
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // do_login function
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (validateUser(username, password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect("user_page");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    private boolean validateUser(String username, String password) {
        // Dummy validation logic
        return "admin".equals(username) && "password".equals(password);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Third function (GET request)
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
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // admin_page function
        if ("admin".equals(request.getSession().getAttribute("user"))) {
            request.getRequestDispatcher("admin_page.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }
}