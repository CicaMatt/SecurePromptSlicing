import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
import java.sql.*; 
public class Login extends HttpServlet { 
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
        String username = request.getParameter("username"); 
        String password = request.getParameter("password"); 
        Connection connection = null; 
        Statement statement = null; 
        ResultSet resultSet = null; 
        String url = "jdbc:mysql://localhost:3306/"; 
        String dbName = "test"; 
        String driver = "com.mysql.cj.jdbc.Driver"; 
        try { 
            Class.forName(driver).newInstance(); 
            connection = DriverManager.getConnection(url + dbName, "root", ""); 
            statement = connection.createStatement(); 
            String query = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'"; 
            resultSet = statement.executeQuery(query); 
            if (resultSet.next()) { 
                response.sendRedirect("home.html"); 
            } else { 
                request.setAttribute("errorMessage", "Invalid credentials"); 
                RequestDispatcher rd = request.getRequestDispatcher("/login.html"); 
                rd.forward(request, response); 
            } 
        } catch (Exception e) { 
            e.printStackTrace(); 
        } finally { 
            if (resultSet != null) { 
                resultSet.close(); 
            } 
            if (statement != null) { 
                statement.close(); 
            } 
            if (connection != null) { 
                connection.close(); 
            } 
        } 
    } 
}