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
        // Handle login GET request
        response.getWriter().write("Login Page");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.getWriter().write("Login Successful");
        } else {
            response.getWriter().write("Invalid Credentials");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "user".equals(username) && "pass".equals(password);
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle do_login POST request
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.getWriter().write("Do Login Successful");
        } else {
            response.getWriter().write("Invalid Credentials for Do Login");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "user".equals(username) && "pass".equals(password);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle index GET request
        response.getWriter().write("Index Page");
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle user_page GET request
        response.getWriter().write("User Page");
    }
}

@WebServlet("/another_page")
public class AnotherPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Handle another_page GET request
        response.getWriter().write("Another Page");
    }
}