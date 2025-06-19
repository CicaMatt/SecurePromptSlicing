import java.io.*;
import java.net.*;
import javax.servlet.http.*;
public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        User user = User.findByUsernameAndPassword(username, password);
        if (user != null) {
            // redirect to home page
            response.sendRedirect("/home.html");
        } else {
            // redirect to login page
            response.sendRedirect("/login.html");
        }
    }
}