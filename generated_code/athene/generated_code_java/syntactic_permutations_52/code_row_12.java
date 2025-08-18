import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (doLogin(username, password)) {
            PrintWriter out = response.getWriter();
            response.setContentType("text/html");
            out.println("<html><body>");
            out.println("<h1>Secret settings</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login.html?error=1");
        }
    }

    private boolean doLogin(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
    }
}