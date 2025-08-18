import java.io.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String action = request.getParameter("action");
        if ("login".equals(action)) {
            showLoginPage(response);
        } else if ("secret".equals(action)) {
            showSecretPage(request, response);
        } else {
            showIndexPage(response);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (doLogin(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("index?action=secret");
        } else {
            response.getWriter().println("Invalid credentials. Please try again.");
            showLoginPage(response);
        }
    }

    private boolean doLogin(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
    }

    private void showIndexPage(HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<a href='index?action=login'>Login</a>");
        out.println("</body></html>");
    }

    private void showLoginPage(HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form method='post' action='index'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form></body></html>");
    }

    private void showSecretPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Secret settings</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("index?action=login");
        }
    }
}