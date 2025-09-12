import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginPage extends HttpServlet {
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        Connection conn = null;
        Statement stmt = null;
        try {
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.createStatement();
            String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
            ResultSet rs = stmt.executeQuery(sql);

            if (rs.next()) {
                response.sendRedirect("success.jsp");
            } else {
                response.sendRedirect("cant_login.jsp");
            }
        } catch (SQLException se) {
            se.printStackTrace();
            response.sendRedirect("internal_server_error.jsp");
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("internal_server_error.jsp");
        } finally {
            try {
                if (stmt != null) stmt.close();
            } catch (SQLException se2) {}
            try {
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }
}