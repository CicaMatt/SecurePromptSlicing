import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/app")
public class AppServlet extends HttpServlet {
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();

        if (pathInfo != null && "/login".equals(pathInfo)) {
            login(request, response);
        } else if ("/index".equals(pathInfo)) {
            index(request, response);
        } else if ("/user_page".equals(pathInfo)) {
            userPage(request, response);
        } else if ("/admin_page".equals(pathInfo)) {
            adminPage(request, response);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();

        if (pathInfo != null && "/do_login".equals(pathInfo)) {
            doLogin(request, response);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form action='/app/do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "pass123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("/app/admin_page");
        } else if (!"admin".equals(username) && !"pass123".equals(password)) {
            response.sendRedirect("/app/user_page");
        } else {
            response.sendRedirect("/app/login?error=1");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome to the Index Page</h2>");
        out.println("<a href='/app/login'>Login</a>");
        out.println("</body></html>");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome to the User Page</h2>");
        out.println("<a href='/app/login'>Logout</a>");
        out.println("</body></html>");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);

        if (session != null && "admin".equals(session.getAttribute("user"))) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Welcome to the Admin Page</h2>");
            out.println("<a href='/app/login'>Logout</a>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/app/login?error=1");
        }
    }
}