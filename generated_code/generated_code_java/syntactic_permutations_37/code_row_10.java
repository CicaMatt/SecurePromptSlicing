import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.lang3.*;
public class login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
            // Validate user input
            String username = request.getParameter("username");
            if (StringUtils.isBlank(username)) {
                response.sendRedirect("/cant_login");
                return;
            }
            String password = request.getParameter("password");
            if (StringUtils.isBlank(password)) {
                response.sendRedirect("/cant_login");
                return;
            }
            // Check user credentials
            if (!username.equals("admin") || !password.equals("password")) {
                response.sendRedirect("/cant_login");
                return;
            }
            // Redirect to success page
            response.sendRedirect("/success");
        }
    }