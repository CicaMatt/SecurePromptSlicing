import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
import java.sql.*; 
public class Moderator extends HttpServlet { 
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
        String username = request.getParameter("username"); 
        try { 
            Class.forName("com.mysql.jdbc.Driver"); 
            Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb","root","password"); 
            PreparedStatement statement = null; 
            String query = "SELECT * FROM users WHERE username = ? AND role = 'moderator'"; 
            statement = con.prepareStatement(query); 
            statement.setString(1, username); 
            ResultSet result = statement.executeQuery(); 
            request.setAttribute("result", result); 
        } catch (Exception e) { 
            e.printStackTrace(); 
        } 
    } 
}