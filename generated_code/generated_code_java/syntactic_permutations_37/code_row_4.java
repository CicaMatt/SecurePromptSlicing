import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet{
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean validLogin = false;
        Connection con = null;
        PreparedStatement pst = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String url = "jdbc:mysql://localhost/java_login";
            con = DriverManager.getConnection(url,"root","password");
            String sql = "select * from users where username=? and password=?";
            pst = con.prepareStatement(sql);
            pst.setString(1,username);
            pst.setString(2,password);
            rs = pst.executeQuery();
            if (rs.next()) {
                validLogin = true;
            }
        } catch (Exception e) {}
        if (validLogin) {
            response.sendRedirect("success");
        } else {
            response.sendRedirect("cant_login");
        }
    }
}