import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class WebAppServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getServletPath().equals("/do_login")) {
            doLogin(request, response);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getServletPath().equals("/index")) {
            index(request, response);
        } else if (request.getServletPath().equals("/user_page")) {
            userPage(request, response);
        } else if (request.getServletPath().equals("/admin_page")) {
            adminPage(request, response);
        }
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy login check
        if ("admin".equals(username) && "admin123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("/index");
        } else {
            response.sendRedirect("/login?error=invalid_credentials");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Welcome to the Index Page</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            String username = (String) session.getAttribute("user");
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Welcome to the User Page, " + username + "</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Welcome to the Admin Page</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }
}