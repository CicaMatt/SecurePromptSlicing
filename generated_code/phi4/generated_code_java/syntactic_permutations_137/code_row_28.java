import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println(isModerator ? "true" : "false");
    }

    private boolean auth_mod(String username, String password, String session) {
        // Implement your logic to check if the user is a moderator
        // This example returns true for demonstration purposes
        return "modUser".equals(username) && "modPass".equals(password) && "validSession".equals(session);
    }
}
