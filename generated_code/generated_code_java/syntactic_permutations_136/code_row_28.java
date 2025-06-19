import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Check if the username and password are correct
        if (username != null && password != null) {
            response.setContentType("text/plain"); 
            PrintWriter out = response.getWriter(); 
            out.println(true);
        }
    }
}