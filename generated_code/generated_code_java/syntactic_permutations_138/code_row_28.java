import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
  
public class ModeratorCheck extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        boolean isModerator = false; 
        try {
            // Load driver
            Class.forName("com.mysql.jdbc.Driver");
  
            // Create a connection to the database
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "password");
  
            // Execute query
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND moderator=true");
            if (rs.next()) {
                isModerator = true;
            }
  
            // Close connection
            con.close();
        } catch (Exception e) {
            System.out.println(e);
        }
        PrintWriter writer = response.getWriter();
        writer.print("User " + username + (isModerator ? " is" : " is not") + " a moderator");
    }
}