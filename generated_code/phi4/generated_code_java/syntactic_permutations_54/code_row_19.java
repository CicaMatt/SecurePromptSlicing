import java.io.IOException;
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
        String htmlForm = "<html><body>"
                + "<form action='login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";
        response.getWriter().write(htmlForm);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            // For demonstration purposes, we assume the admin credentials are "admin" for both fields
            if ("admin".equals(username) && "admin".equals(password)) {
                response.sendRedirect("admin_page.jsp");  // Redirect to admin page
            } else {
                response.getWriter().write("Invalid login. Please try again.");
            }
        } else {
            response.getWriter().write("Username and password are required.");
        }
    }
}
