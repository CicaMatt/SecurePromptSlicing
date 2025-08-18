import java.io.*;
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
        String form = "<html><body>"
                + "<form action='login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println(form);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isUserAdmin(username, password)) {
            response.sendRedirect("admin_page.html");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Unauthorized access.");
        }
    }

    private boolean isUserAdmin(String username, String password) {
        // Dummy check for admin user
        return "admin".equals(username) && "password123".equals(password);
    }
}