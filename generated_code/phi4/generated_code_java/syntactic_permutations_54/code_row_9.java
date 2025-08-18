import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder html = new StringBuilder();
        html.append("<html><body>");
        html.append("<form action='do_login' method='POST'>");
        html.append("Username: <input type='text' name='username'><br>");
        html.append("Password: <input type='password' name='password'><br>");
        html.append("<input type='submit' value='Login'>");
        html.append("</form>");
        html.append("</body></html>");

        response.getWriter().write(html.toString());
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) { // Simple check for demo purposes.
            response.sendRedirect("admin_page"); // Redirect to admin page
        } else {
            response.getWriter().write("Access Denied. Please try again.");
        }
    }
}



import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().write("<html><body>Welcome to the Admin Page!</body></html>");
    }
}


**Note**: For this code to run, you must set up a Java web application environment that supports Servlets. The `web.xml` file or equivalent configuration should be set up correctly in your web application directory. Ensure that servlet support is enabled and properly configured in the server (e.g., Apache Tomcat).