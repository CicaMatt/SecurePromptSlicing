import java.io.*;

import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPage extends HttpServlet {
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response) {
        try {
            PrintWriter out = response.getWriter();
            out.println("<html>");
            out.println("<body>");
            out.println("<form method=\"post\" action=\"/do_login\">");
            out.println("Username: <input type=\"text\" name=\"username\" /><br/>");
            out.println("Password: <input type=\"password\" name=\"password\" /><br/>");
            out.println("<input type=\"submit\" value=\"Login\" />");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
        } catch (IOException e) {
            //handle exception
        }
    }
}

public class DoLogin extends HttpServlet {
    public void doPost(HttpServletRequest request, 
                       HttpServletResponse response) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("/secretpage");
        } else {
            // authentication failed
        }
    }

    private boolean authenticate(String username, String password) {
        // check the database
        return true;
    }
}

public class SecretPage extends HttpServlet {
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response) {
        try {
            PrintWriter out = response.getWriter();
            out.println("<html>");
            out.println("<body>");
            out.println("Secret settings");
            out.println("</body>");
            out.println("</html>");
        } catch (IOException e) {
            //handle exception
        }
    }
}