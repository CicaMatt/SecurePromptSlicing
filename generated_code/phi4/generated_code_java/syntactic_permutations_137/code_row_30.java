import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String sessionID = request.getParameter("session");

        if (authMod(username, password, sessionID)) {
            response.getWriter().write("Authentication Successful");
        } else {
            response.getWriter().write("Authentication Failed");
        }
    }

    private boolean authMod(String username, String password, String session) {
        // Simulating authentication logic
        return true;
    }
}