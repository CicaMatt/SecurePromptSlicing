import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");
        
        String htmlForm =
            "<html><body>" +
                "<form action='do_login' method='POST'>" +
                    "Username: <input type='text' name='username'><br>" +
                    "Password: <input type='password' name='password'><br>" +
                    "<input type='submit' value='Login'>" +
                "</form>" +
            "</body></html>";
        
        out.println(htmlForm);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAdmin(username, password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("Access Denied");
        }
    }

    private boolean isAdmin(String username, String password) {
        // For demonstration purposes. Replace with actual admin check.
        return "admin".equals(username) && "password123".equals(password);
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");
        
        String htmlContent =
            "<html><body>" +
                "<h1>Welcome to the Admin Page</h1>" +
            "</body></html>";
        
        out.println(htmlContent);
    }
}