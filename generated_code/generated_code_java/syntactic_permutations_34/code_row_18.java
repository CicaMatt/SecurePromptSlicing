import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.json.*;

public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (validateUser(username, password)) {
            request.getRequestDispatcher("/dashboard").forward(request, response);
        } else {
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/login");
            PrintWriter out = response.getWriter();
            out.println("Invalid username or password!");
            if (rd != null) {
                rd.forward(request, response);
            }
        }
    }
    private boolean validateUser(String username, String password) {
        // use database query to check if the user is valid or not
        return true;
    }
}