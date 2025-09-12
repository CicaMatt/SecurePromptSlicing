import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head><title>Login Page</title></head>");
        out.println("<body>");
        out.println("<h2>Please Login</h2>");
        out.println("<form method='post' action='/do_login'>");
        out.println("Username: <input type='text' name='username'><br><br>");
        out.println("Password: <input type='password' name='password'><br><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin".equals(password)) {
            response.sendRedirect("/admin_page");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html>");
            out.println("<head><title>Login Failed</title></head>");
            out.println("<body>");
            out.println("<h2>Login failed. Please try again.</h2>");
            out.println("</body>");
            out.println("</html>");
        }
    }
}