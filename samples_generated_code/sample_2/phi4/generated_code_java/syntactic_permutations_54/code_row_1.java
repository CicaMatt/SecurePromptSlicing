import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String form = "<html><body>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";
        
        out.println(form);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            if ("admin".equals(username) && "password123".equals(password)) { // Example credentials
                response.sendRedirect("admin_page.jsp"); // Redirect to admin page
            } else {
                response.setContentType("text/html");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");
                out.println("<p>Login failed. Please try again.</p>");
                out.println("</body></html>");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid Request");
        }
    }
}
