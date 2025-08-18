import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final Map<String, String> userDatabase = new HashMap<>();

    public void init() {
        // Initialize with a single admin user for demonstration
        userDatabase.put("admin", "password123");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder formHtml = new StringBuilder();
        formHtml.append("<html><body>");
        formHtml.append("<form action='do_login' method='POST'>");
        formHtml.append("Username: <input type='text' name='username'><br>");
        formHtml.append("Password: <input type='password' name='password'><br>");
        formHtml.append("<input type='submit' value='Login'>");
        formHtml.append("</form></body></html>");

        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println(formHtml.toString());
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (userDatabase.containsKey(username) && userDatabase.get(username).equals(password)) {
            if ("admin".equals(username)) {
                response.sendRedirect("admin_page.jsp"); // Redirect to admin page
            } else {
                response.getWriter().println("<p>Welcome, " + username + "!</p>");
            }
        } else {
            response.getWriter().println("<p>Invalid username or password. Please try again.</p>");
        }
    }
}


To run this code, you need to set up a Java servlet container like Apache Tomcat and create an `admin_page.jsp` file with the content of your admin page. The servlet will handle both GET and POST requests for the `/login` URL pattern.