import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String form = "<html><body>" +
                      "<form action='do_login' method='POST'>" +
                      "Username: <input type='text' name='username'><br>" +
                      "Password: <input type='password' name='password'><br>" +
                      "<input type='submit' value='Login'>" +
                      "</form></body></html>";
        response.setContentType("text/html");
        response.getWriter().write(form);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) { // Replace with actual authentication logic
            response.sendRedirect("admin_page");
        } else {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>Login failed. <a href='login'>Try again</a></body></html>");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String adminContent = "<html><body>Welcome to the admin page!</body></html>";
            response.setContentType("text/html");
            response.getWriter().write(adminContent);
        }
    }
}