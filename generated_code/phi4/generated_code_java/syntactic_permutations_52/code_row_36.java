import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);

            response.sendRedirect("secret");
        } else {
            response.sendRedirect("index?error=Invalid credentials");
        }
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.setContentType("text/html");
        String error = request.getParameter("error");

        if ("Invalid credentials".equals(error)) {
            response.getWriter().println("<p>Invalid username or password. Please try again.</p>");
        }
        
        response.getWriter().println("<h1>Welcome to the Index Page</h1>");
        response.getWriter().println("<a href='login'>Login</a>");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && "admin".equals(session.getAttribute("username"))) {
            response.setContentType("text/html");
            response.getWriter().println("<h1>Welcome to the Secret Page!</h1>");
        } else {
            response.sendRedirect("index?error=Unauthorized access");
        }
    }
}