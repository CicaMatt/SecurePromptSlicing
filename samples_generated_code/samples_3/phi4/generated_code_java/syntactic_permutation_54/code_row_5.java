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
        
        String formHtml = "<html><body>"
                        + "<form action='do_login' method='POST'>"
                        + "Username: <input type='text' name='username'><br>"
                        + "Password: <input type='password' name='password'><br>"
                        + "<input type='submit' value='Login'>"
                        + "</form>"
                        + "</body></html>";
        
        out.println(formHtml);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) {
            response.sendRedirect("/admin_dashboard"); // Redirect to admin dashboard URL
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h3>Invalid credentials. Please try again.</h3>");
            out.println("</body></html>");
        }
    }
}


Make sure that the servlet container is set up correctly and that you have a URL mapping to `/admin_dashboard` in your web application configuration if this is an actual admin dashboard route you are redirecting to.