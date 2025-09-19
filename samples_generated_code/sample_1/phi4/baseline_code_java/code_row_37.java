import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String html = "<html><body>"
                + "<h2>Login</h2>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form>"
                + "</body></html>";
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println(html);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("Invalid credentials.");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {

        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            String html = "<html><body>"
                    + "<h2>Welcome, Admin</h2>"
                    + "</body></html>";
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println(html);
        }
    }
}
