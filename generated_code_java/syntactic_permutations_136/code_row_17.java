import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (check_mod(username, password)) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("true");
        }
    }

    public boolean check_mod(String username, String password) {
        // connect to the database
        if (username.equals("admin") && password.equals("password")) {
            return true;
        } else {
            return false;
        }
    }
}