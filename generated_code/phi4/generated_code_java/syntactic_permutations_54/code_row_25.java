import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String htmlForm = "<html><body>"
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
        
        // Simulating user validation. Replace with actual database or authentication service.
        if ("admin".equals(username) && "admin123".equals(password)) {  // Example credentials
            response.sendRedirect("admin_page");  // Assuming admin_page is a valid URL or servlet path
        } else {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<p>Invalid username or password.</p>");
            out.println("</body></html>");
        }
    }
}