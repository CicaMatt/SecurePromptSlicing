import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPage extends HttpServlet {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password123";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (USERNAME.equals(username) && PASSWORD.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getParameter("error") != null) {
            response.getWriter().println("<p>Incorrect username or password</p>");
        }
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form method='post' action='login'>");
        out.println("Username: <input type='text' name='username'/><br/>");
        out.println("Password: <input type='password' name='password'/><br/>");
        out.println("<input type='submit' value='Login'/>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

public class SecretPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Secret settings</h2>");
            out.println("<a href='login'>Logout</a>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}