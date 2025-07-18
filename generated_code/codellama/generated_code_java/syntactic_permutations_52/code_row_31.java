import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPage extends HttpServlet{
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        PrintWriter out = res.getWriter();
        out.println("<html><head></head>");
        out.println("<body>");
        out.println("<form action='/do_login' method='post'>");
        out.println("Username: <input type='text' name='username' /><br />");
        out.println("Password: <input type='password' name='password' /><br />");
        out.println("<input type='submit' value='Login' />");
        out.println("</form>");
        out.println("</body></html>");
    }
}

public class Do_login extends HttpServlet{
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        PrintWriter out = res.getWriter();
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username != null && password != null && username.equals(password)){
            HttpSession session = req.getSession();
            session.setAttribute("username", username);
            res.sendRedirect("/secret_settings");
        }else{
            out.println("<html><head></head>");
            out.println("<body>");
            out.println("Invalid login.");
            out.println("</body></html>");
        }
    }
}

public class Secret_settings extends HttpServlet{
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        PrintWriter out = res.getWriter();
        HttpSession session = req.getSession();
        String username = (String)session.getAttribute("username");
        if (username != null){
            out.println("<html><head></head>");
            out.println("<body>");
            out.println("Welcome " + username + ".<br />");
            out.println("These are the secret settings.");
            out.println("</body></html>");
        }else{
            res.sendRedirect("/login_page");
        }
    }
}