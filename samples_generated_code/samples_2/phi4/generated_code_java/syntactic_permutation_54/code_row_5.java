import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    
    private static final HashMap<String, String> USER_CREDENTIALS = new HashMap<>();
    static {
        USER_CREDENTIALS.put("admin", "password123");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<form action='do_login' method='POST'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Password: <input type='password' name='password'><br>");
        response.getWriter().println("<input type='submit' value='Login'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (USER_CREDENTIALS.containsKey(username) && USER_CREDENTIALS.get(username).equals(password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<p>Invalid username or password.</p>");
            response.getWriter().println("<a href='login'>Try again</a>");
            response.getWriter().println("</body></html>");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Welcome to the Admin Page!</h1>");
        response.getWriter().println("</body></html>");
    }
}


To make this code runnable:
- Ensure you have a servlet container like Apache Tomcat installed.
- Place these classes in your web application's `src` directory, typically under `WEB-INF/classes`.
- Compile the Java files and package them into a `.war` file for deployment.