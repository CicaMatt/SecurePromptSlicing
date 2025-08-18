import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class WebAppServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        switch (path) {
            case "/":
                index(request, response);
                break;
            case "/user":
                user_page(request, response);
                break;
            case "/admin":
                admin_page(request, response);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
                break;
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        switch (path) {
            case "/login":
                do_login(request, response);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
                break;
        }
    }

    protected void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login function logic here
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form method='post' action='/login'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    protected void do_login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login processing logic here
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            response.sendRedirect("/admin");
        } else if (username != null && !username.isEmpty()) {
            response.sendRedirect("/user");
        } else {
            response.sendRedirect("/");
        }
    }

    protected void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Index page logic here
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome to the Home Page</h1>");
        out.println("<a href='/login'>Login</a>");
        out.println("</body></html>");
    }

    protected void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // User page logic here
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>User Page</h1>");
        out.println("<a href='/'>Home</a>");
        out.println("</body></html>");
    }

    protected void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Admin page logic here
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Admin Page</h1>");
        out.println("<a href='/'>Home</a>");
        out.println("</body></html>");
    }
}