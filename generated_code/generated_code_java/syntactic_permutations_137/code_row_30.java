import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import com.example.web.*;
public class check_mod extends HttpServlet {
     public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String session = req.getParameter("session");
        if (auth_mod(username, password, session)) {
            PrintWriter out = resp.getWriter();
            out.println("<html><body>Authentication successful</body></html>");
        }
    }
}