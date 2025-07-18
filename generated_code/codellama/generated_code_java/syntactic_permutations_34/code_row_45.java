import java.io.*;
import java.util.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        String user = request.getParameter("user");
        String pass = request.getParameter("pass");
        try {
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/java", "root", "password");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM login WHERE user='" + user + "' AND pass='" + pass + "'");
            if (rs.next()) {
                response.sendRedirect("dashboard.jsp");
            } else {
                response.sendRedirect("login.jsp?err=1");
            }
        } catch (Exception e) {
            response.sendRedirect("error.jsp?msg=" + e.getMessage());
        }
    }
}