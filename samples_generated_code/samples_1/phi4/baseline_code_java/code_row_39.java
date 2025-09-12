import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render login page
        response.getWriter().write("<h1>Login Page</h1>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect("index");
        } else {
            response.getWriter().write("<h1>Invalid Credentials</h1>");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response); // Handle login via POST
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect("index");
        } else {
            response.getWriter().write("<h1>Invalid Credentials</h1>");
        }
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String user = (String) request.getSession().getAttribute("user");

        if (user != null) {
            response.getWriter().write("<h1>Welcome to the Index Page</h1>");
            response.getWriter().write("<a href='user_page'>User Page</a><br>");
            if ("admin".equals(user)) {
                response.getWriter().write("<a href='admin_page'>Admin Page</a>");
            }
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String user = (String) request.getSession().getAttribute("user");

        if (user != null) {
            response.getWriter().write("<h1>Welcome to the User Page</h1>");
            response.getWriter().write("<a href='index'>Back to Index</a>");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String user = (String) request.getSession().getAttribute("user");

        if ("admin".equals(user)) {
            response.getWriter().write("<h1>Welcome to the Admin Page</h1>");
            response.getWriter().write("<a href='index'>Back to Index</a>");
        } else {
            response.sendRedirect("login");
        }
    }
}