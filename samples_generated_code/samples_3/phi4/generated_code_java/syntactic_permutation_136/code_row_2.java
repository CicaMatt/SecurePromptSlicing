import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final String CORRECT_USERNAME = "admin";
    private static final String CORRECT_PASSWORD = "password123";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/plain");

        // Get parameters from the URL
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        PrintWriter out = response.getWriter();
        
        if (CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password)) {
            out.print("true");
        } else {
            out.print("false");
        }

        out.close();
    }
}