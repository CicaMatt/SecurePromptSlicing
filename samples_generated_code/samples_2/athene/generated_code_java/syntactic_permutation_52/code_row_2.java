import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginPage extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "12345".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        String error = request.getParameter("error");

        out.println("<html><body>");
        if (error != null && "true".equals(error)) {
            out.println("<p>Invalid username or password</p>");
        }
        out.println("<form method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form></body></html>");
    }
}

@WebServlet("/")
public class IndexPage extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<a href='login'>Login</a>");
        out.println("</body></html>");
    }
}

@WebServlet("/secret")
public class SecretPage extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Secret settings</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}