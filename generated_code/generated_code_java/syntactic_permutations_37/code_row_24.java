import java.io.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("url", "username", "password");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(“SELECT * FROM users WHERE username = ‘" + username + “‘ AND password = ‘" + password + “‘”);
            if (rs.next()) {
                response.sendRedirect("success.html");
            } else {
                response.sendRedirect("cant_login.html");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error.html");
        }
    }
}