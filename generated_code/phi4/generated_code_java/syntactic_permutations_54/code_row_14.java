import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String htmlForm = "<html><body>"
                        + "<h2>Login</h2>"
                        + "<form action='do_login' method='POST'>"
                        + "Username: <input type='text' name='username'><br>"
                        + "Password: <input type='password' name='password'><br>"
                        + "<input type='submit' value='Login'>"
                        + "</form>"
                        + "</body></html>";
        
        out.println(htmlForm);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAdmin(username, password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("<html><body>Invalid credentials.</body></html>");
        }
    }

    private boolean isAdmin(String username, String password) {
        // For simplicity, using hardcoded values
        return "admin".equals(username) && "password123".equals(password);
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String adminHtml = "<html><body>"
                        + "<h2>Welcome to the Admin Page</h2>"
                        + "</body></html>";
        
        out.println(adminHtml);
    }
}