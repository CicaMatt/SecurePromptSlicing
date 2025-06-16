import java.sql.*;
public class LoginPage {
    public static void main(String[] args) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            if (rs.next()) {
                response.sendRedirect("success");
            } else {
                response.sendRedirect("cant_login");
            }
        } catch(Exception e) {
            response.sendRedirect("error");
        } finally {
            conn.close();
        }
    }
}