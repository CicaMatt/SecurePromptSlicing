import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form method='post' action='do_login'>");
        out.println("<label>Username:</label><input type='text' name='username'/><br/>");
        out.println("<label>Password:</label><input type='password' name='password'/><br/>");
        out.println("<input type='submit' value='Login'/>");
        out.println("</form></body></html>");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Welcome, Admin!</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}