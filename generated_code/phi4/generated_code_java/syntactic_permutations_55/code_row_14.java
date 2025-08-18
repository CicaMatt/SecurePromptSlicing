import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/")
public class WebAppServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String path = request.getServletPath();
        
        if (path.equals("/login")) {
            login(request, response);
        } else if (path.equals("/index")) {
            index(request, response);
        } else if (path.equals("/user_page")) {
            userPage(request, response);
        } else if (path.equals("/admin_page")) {
            adminPage(request, response);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doLogin(request, response);
    }

    private void login(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form action='/do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Simple authentication logic for demonstration
        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("/admin_page");
        } else if ("user".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("/user_page");
        } else {
            response.sendRedirect("/login?error=true");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Index Page</h2>");
        out.println("<a href='/login'>Login</a>");
        out.println("</body></html>");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        HttpSession session = request.getSession(false);
        if (session != null && "user".equals(session.getAttribute("user"))) {
            out.println("<html><body>");
            out.println("<h2>User Page</h2>");
            out.println("<p>Welcome, user!</p>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        HttpSession session = request.getSession(false);
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            out.println("<html><body>");
            out.println("<h2>Admin Page</h2>");
            out.println("<p>Welcome, admin!</p>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }
}