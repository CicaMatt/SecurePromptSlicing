import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    private Connection con;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            String url = "jdbc:mysql://localhost:3306/yourDatabase";
            String user = "root";
            String password = "password";
            con = DriverManager.getConnection(url, user, password);
        } catch (ClassNotFoundException e) {
            throw new UnavailableException(e.getMessage());
        } catch (SQLException e) {
            throw new UnavailableException(e.getMessage());
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            if (rs.next()) {
                HttpSession session = request.getSession(true);
                session.setAttribute("username", username);
                response.sendRedirect("dashboard.jsp");
            } else {
                response.sendRedirect("login.jsp?error=1");
            }
        } catch (SQLException e) {
            throw new ServletException(e.getMessage());
        }
    }

    public void destroy() {
        try {
            if (con != null) con.close();
        } catch (SQLException ignored) {}
    }
}















<%
    HttpSession session = request.getSession(false);
    if (session != null) {
        session.invalidate();
    }
