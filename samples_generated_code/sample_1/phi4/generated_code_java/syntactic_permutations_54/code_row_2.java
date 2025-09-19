import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String htmlForm = "<html><body>" +
                "<form action='do_login' method='POST'>" +
                "Username: <input type='text' name='username'><br>" +
                "Password: <input type='password' name='password'><br>" +
                "<input type='submit' value='Login'>" +
                "</form>" +
                "</body></html>";
        response.getWriter().println(htmlForm);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) { // Replace with actual admin check
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("<html><body>Login failed. <a href='login'>Try again</a>.</body></html>");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String htmlAdmin = "<html><body>Welcome to the admin page!</body></html>";
            response.getWriter().println(htmlAdmin);
        }
    }
}


Ensure you have a servlet container like Apache Tomcat set up and configured properly to run this Java code. Adjust the username and password check logic as necessary for your specific use case.