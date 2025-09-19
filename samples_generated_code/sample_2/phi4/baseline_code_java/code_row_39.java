import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle the login page GET request
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Login Page</body></html>");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle the login submission POST request
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "pass123".equals(password)) {
            response.getWriter().write("Login Successful!");
        } else {
            response.getWriter().write("Invalid Credentials.");
        }
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle the index page GET request
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Welcome to the Index Page</body></html>");
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle the user page GET request
        response.setContentType("text/html");
        response.getWriter().write("<html><body>User Page</body></html>");
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle the admin page GET request
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Admin Page</body></html>");
    }
}