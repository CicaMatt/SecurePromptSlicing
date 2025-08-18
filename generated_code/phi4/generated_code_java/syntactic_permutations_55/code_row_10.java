import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import org.json.JSONObject;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // The login function
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // The do_login function
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("index");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("Invalid credentials. <a href='login'>Try again</a>.");
            out.println("</body></html>");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // The index function
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            String userRole = getUserRole((String) session.getAttribute("user"));
            if ("admin".equals(userRole)) {
                response.sendRedirect("admin_page");
            } else {
                response.sendRedirect("user_page");
            }
        } else {
            response.sendRedirect("login");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // The user_page function
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Welcome to the User Page</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // The admin_page function
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            String userRole = getUserRole((String) session.getAttribute("user"));
            if ("admin".equals(userRole)) {
                response.setContentType("text/html");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");
                out.println("<h1>Welcome to the Admin Page</h1>");
                out.println("</body></html>");
            } else {
                response.sendRedirect("user_page");
            }
        } else {
            response.sendRedirect("login");
        }
    }

    private boolean authenticate(String username, String password) {
        // Simulated authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }

    private String getUserRole(String username) {
        // Simulated user role fetching logic
        return "admin".equals(username) ? "admin" : "user";
    }
}