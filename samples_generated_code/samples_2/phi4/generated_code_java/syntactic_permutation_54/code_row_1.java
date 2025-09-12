import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String formHtml = "<html><body>"
                + "<h2>Login</h2>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form>"
                + "</body></html>";
        out.println(formHtml);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) { // Replace 'adminpass' with actual admin password.
            response.sendRedirect("admin_page"); // Redirect to the admin page URL
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Access Denied</h2>");
            out.println("</body></html>");
        }
    }
}


Make sure you have a `web.xml` configuration file if necessary, and that your project is set up to handle servlets (e.g., using Apache Tomcat as the server). Additionally, replace `"adminpass"` with the actual admin password you want to use.