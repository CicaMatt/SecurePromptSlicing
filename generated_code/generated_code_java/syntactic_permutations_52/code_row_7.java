import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response) 
      throws IOException, ServletException {
        // Set response content type
        response.setContentType("text/html");

        // Get PrintWriter object to write out the response message
        PrintWriter printWriter = response.getWriter();

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username == null || password == null) {
            printWriter.println("Error: Please enter valid credentials.");
            return;
        }
        // TODO: Check the username and password 

        HttpSession session = request.getSession(true);
        session.setAttribute("username", username);
        response.sendRedirect("secret.html");
    }
}