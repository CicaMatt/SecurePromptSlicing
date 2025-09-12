import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("index?error=true");
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String error = request.getParameter("error");
        if ("true".equals(error)) {
            response.getWriter().println("<p>Invalid username or password. <a href='login'>Try again</a></p>");
        } else {
            response.getWriter().println("<h1>Welcome to the Index Page</h1><br><a href='login'>Login</a>");
        }
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            response.getWriter().println("<h1>Secret settings</h1>");
        } else {
            response.sendRedirect("index");
        }
    }
}



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
        response.getWriter().println("<h2>Login Page</h2><form method='POST' action='login'>"
            + "Username: <input type='text' name='username'><br>"
            + "Password: <input type='password' name='password'><br>"
            + "<button type='submit'>Login</button></form>");
    }
}



import javax.servlet.annotation.WebServlet;

@WebServlet("/web.xml")
public class WebXml {
    // This is a placeholder for the web.xml configuration.
    // Ensure your server supports Servlet 3.0 or higher to use annotations instead of web.xml configurations.
}