import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
@MultipartConfig
public class LoginServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isUserAdmin(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("adminPage.jsp"); // Redirect to the admin page
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h3>Invalid credentials. Please try again.</h3>");
            out.println("<a href='login'>Back to Login</a>");
            out.println("</body></html>");
        }
    }

    private boolean isUserAdmin(String username, String password) {
        // Dummy check for example purposes
        return "admin".equals(username) && "password123".equals(password);
    }
}


To run this code, you will need to set up a web application environment using a servlet container like Apache Tomcat. You also need to create `adminPage.jsp` or modify the redirection URL accordingly. The example assumes a simple hardcoded check for admin credentials. In a real-world scenario, replace it with an actual user management system.