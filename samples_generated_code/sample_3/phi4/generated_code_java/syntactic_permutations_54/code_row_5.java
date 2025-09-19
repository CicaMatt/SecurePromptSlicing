import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    
    private static final HashMap<String, String> users = new HashMap<>();

    public void init() {
        // Adding a sample admin user for demonstration purposes
        users.put("admin", "password123");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<form action='login' method='POST'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Password: <input type='password' name='password'><br>");
        response.getWriter().println("<input type='submit' value='Login'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (users.containsKey(username) && users.get(username).equals(password)) {
            if ("admin".equalsIgnoreCase(username)) {
                response.sendRedirect("admin_page.jsp"); // Assuming 'admin_page.jsp' exists
            } else {
                // Handle non-admin login success, redirect or display message as needed
                response.getWriter().println("<html><body>Logged in successfully as a user.</body></html>");
            }
        } else {
            response.getWriter().println("<html><body>Login failed. Please try again.</body></html>");
        }
    }
}
