import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
    private String getPassword(String username, Connection conn) throws SQLException {
        Statement stmt = null;
        ResultSet rs = null;
        String password = null;

        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT password FROM users WHERE username='" + username + "'");

            if (rs.next()) {
                password = rs.getString("password");
            } else {
                return null;
            }
        } catch (SQLException e) {
            throw new SQLException(e);
        } finally {
            if (stmt != null) {
                stmt.close();
            }
            if (rs != null) {
                rs.close();
            }
        }

        return password;
    }

    private boolean checkUser(String username, String password, Connection conn) throws SQLException {
        Statement stmt = null;
        ResultSet rs = null;

        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");

            if (rs.next()) {
                return true;
            } else {
                return false;
            }
        } catch (SQLException e) {
            throw new SQLException(e);
        } finally {
            if (stmt != null) {
                stmt.close();
            }
            if (rs != null) {
                rs.close();
            }
        }
    }

    private Connection getConnection() throws ClassNotFoundException, SQLException {
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://localhost/login_db";
        String user = "root";
        String password = "";

        Class.forName(driver);
        Connection conn = DriverManager.getConnection(url, user, password);

        return conn;
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            Connection conn = getConnection();
            Statement stmt = null;

            if (checkUser(username, password, conn)) {
                response.sendRedirect("home.html");
            } else {
                response.sendRedirect("login.html?error=1");
            }
        } catch (ClassNotFoundException e) {
            System.out.println(e);
        } catch (SQLException e) {
            System.out.println(e);
        }
    }
}