import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.io.output.*;
  
public class Servlet extends HttpServlet {
    private String username;
    private String password;
  
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        RequestDispatcher view = request.getRequestDispatcher("login.jsp");
        view.forward(request, response);
    }
  
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
  
        if (authenticate(username, password)) {
            RequestDispatcher view = request.getRequestDispatcher("admin_page.jsp");
            view.forward(request, response);
        } else {
            PrintWriter out = response.getWriter();
            out.println("Invalid username or password.");
        }
    }
  
    private boolean authenticate(String username, String password) {
        // Check if the user is in the database
        return true;
    }
}