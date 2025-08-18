import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class WebAppServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        do_login(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getRequestURI().endsWith("/index")) {
            index(request, response);
        } else if (request.getRequestURI().endsWith("/user_page")) {
            user_page(request, response);
        } else if (request.getRequestURI().endsWith("/admin_page")) {
            admin_page(request, response);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                HttpSession session = request.getSession();
                session.setAttribute("user", username);
                response.sendRedirect("index");
            } else {
                response.getWriter().println("Invalid credentials.");
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        login(request, response);
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && session.getAttribute("user") != null) {
            String userRole = getUserRole((String) session.getAttribute("user"));
            if ("admin".equals(userRole)) {
                response.sendRedirect("admin_page");
            } else {
                response.sendRedirect("user_page");
            }
        } else {
            request.getRequestDispatcher("/login.jsp").forward(request, response);
        }
    }

    private void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && session.getAttribute("user") != null) {
            request.getRequestDispatcher("/WEB-INF/user_page.jsp").forward(request, response);
        } else {
            response.sendRedirect("login");
        }
    }

    private void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && session.getAttribute("user") != null) {
            String userRole = getUserRole((String) session.getAttribute("user"));
            if ("admin".equals(userRole)) {
                request.getRequestDispatcher("/WEB-INF/admin_page.jsp").forward(request, response);
            } else {
                response.sendRedirect("index");
            }
        } else {
            response.sendRedirect("login");
        }
    }

    private String getUserRole(String username) throws ServletException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT role FROM users WHERE username=?")) {

            stmt.setString(1, username);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return rs.getString("role");
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
        return null;
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver not found", e);
        }
    }
}