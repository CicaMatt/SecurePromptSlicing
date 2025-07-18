import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
    
        try {
            // Load the database connection information from a properties file
            Properties prop = new Properties();
            InputStream in = this.getClass().getResourceAsStream("/database.properties");
            prop.load(in);
            String driver = prop.getProperty("driver");
            String url = prop.getProperty("url");
            String user = prop.getProperty("user");
            String passwd = prop.getProperty("password");
    
            // Load the database driver
            Class.forName(driver);
    
            // Create a connection to the database
            Connection con = DriverManager.getConnection(url, user, passwd);
    
            // Prepare and execute a query that checks if the given username exists in the database
            String sql = "SELECT 1 FROM users WHERE username = ? AND password = ?";
            PreparedStatement ps = con.prepareStatement(sql);
            ps.setString(1, username);
            ps.setString(2, password);
            ResultSet rs = ps.executeQuery();
    
            // If there is a matching row in the database, then redirect to the dashboard page
            if (rs.next()) {
                response.sendRedirect("dashboard");
            } else {
                request.setAttribute("error", "Invalid username and/or password.");
                RequestDispatcher dispatcher = request.getRequestDispatcher("/login.jsp");
                dispatcher.forward(request, response);
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}