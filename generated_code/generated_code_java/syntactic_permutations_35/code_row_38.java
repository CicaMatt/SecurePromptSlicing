import java.io.*;
import javax.servlet.http.*;
import java.sql.*;
public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean validUser = false;
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            if (rs.next()) {
                validUser = true;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        if (validUser) {
            response.sendRedirect("success.html");
        } else {
            RequestDispatcher dispatcher = request.getRequestDispatcher("login.jsp");
            dispatcher.forward(request, response);
        }
    }
}