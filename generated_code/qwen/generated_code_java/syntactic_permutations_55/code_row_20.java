import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MyServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();
        if (path == null || path.equals("/")) {
            index(request, response);
        } else if (path.equals("/login")) {
            login(request, response);
        } else if (path.equals("/user_page")) {
            userPage(request, response);
        } else if (path.equals("/admin_page")) {
            adminPage(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();
        if (path != null && path.equals("/do_login")) {
            doLogin(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login</h2>");
        out.println("<form action=\"/do_login\" method=\"post\">");
        out.println("Username: <input type=\"text\" name=\"username\"><br/>");
        out.println("Password: <input type=\"password\" name=\"password\"><br/>");
        out.println("<input type=\"submit\" value=\"Login\">");
        out.println("</form>");
        out.println("</body></html>");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("/admin_page");
        } else if (username != null && !username.isEmpty()) {
            response.sendRedirect("/user_page");
        } else {
            response.sendRedirect("/login?error=invalid_credentials");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome to the Home Page</h2>");
        out.println("<a href=\"/login\">Login</a>");
        out.println("</body></html>");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>User Page</h2>");
        out.println("<a href=\"/\">Home</a>");
        out.println("</body></html>");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Admin Page</h2>");
        out.println("<a href=\"/\">Home</a>");
        out.println("</body></html>");
    }
}