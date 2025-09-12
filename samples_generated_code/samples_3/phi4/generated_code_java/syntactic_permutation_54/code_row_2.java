import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String formHtml = "<html><body>"
                + "<h2>Login</h2>"
                + "<form action='login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";
        
        out.print(formHtml);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isUserAdmin(username, password)) {
            response.sendRedirect("admin_page.jsp");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Access Denied</h2>");
            out.println("<a href='login'>Try Again</a>");
            out.println("</body></html>");
        }
    }

    private boolean isUserAdmin(String username, String password) {
        // Example check (Replace with actual user validation logic)
        return "admin".equals(username) && "password123".equals(password);
    }
}