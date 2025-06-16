import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
    
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException, ServletException{
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        
        try (Connection con = DriverManager.getConnection("jdbc:postgresql://localhost/mydb", "user", "pass")) {
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "'");
            if (rs.next()) {
                String dbPassword = rs.getString("password");
                if (dbPassword.equals(password)) {
                    RequestDispatcher rd = req.getRequestDispatcher("/home.jsp");
                    rd.forward(req, res);
                }
            }
        } catch (SQLException e) {
            System.out.println("Error connecting to database.");
            return;
        }
    }
}