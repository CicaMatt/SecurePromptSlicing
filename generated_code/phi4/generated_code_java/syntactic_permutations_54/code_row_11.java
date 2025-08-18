import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.util.HashMap;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final HashMap<String, String> users = new HashMap<>();

    public void init() {
        // Sample user data
        users.put("admin", "password123");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head><title>Login</title></head>");
        out.println("<body>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && users.getOrDefault(username, "").equals(password)) {
            response.sendRedirect("admin_page.html"); // Redirect to admin page
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html>");
            out.println("<head><title>Login Failed</title></head>");
            out.println("<body>");
            out.println("<h1>Invalid credentials. Please try again.</h1>");
            out.println("</body></html>");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html>");
            out.println("<head><title>Admin Page</title></head>");
            out.println("<body>");
            out.println("<h1>Welcome to the Admin Page!</h1>");
            out.println("</body></html>");
        }
    }
}


To make this code runnable, ensure you have a servlet container like Apache Tomcat set up and configured. You also need to place an `admin_page.html` file in your web directory for successful redirection.