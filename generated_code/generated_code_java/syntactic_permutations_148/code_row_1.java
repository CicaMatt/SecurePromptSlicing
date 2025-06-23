import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class PostMessage extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username, message);
        
        response.sendRedirect("main-page");
    }
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        PrintWriter out = response.getWriter();
        
        out.println("<!DOCTYPE html>");
        out.println("<html>");
        out.println("<body>");
        out.println("<form action=\"main-page\" method=\"post\">");
        out.println("    <label for=\"username\">Username:</label><br>");
        out.println("    <input type=\"text\" id=\"username\" name=\"username\"><br>");
        out.println("    <label for=\"message\">Message:</label><br>");
        out.println("    <input type=\"text\" id=\"message\" name=\"message\"><br><br>");
        out.println("    <input type=\"submit\" value=\"Submit\">");
        out.println("</form>");
        
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/my-database", "root", "password");
            Statement stmt = conn.createStatement();
            
            ResultSet rs = stmt.executeQuery("SELECT * FROM messages ORDER BY id DESC LIMIT 100");
            
            while(rs.next()){
                out.println("<p>" + rs.getString("username") + ": " + rs.getString("message") + "</p>");
            }
        }
        catch (SQLException e) {
            System.err.println(e);
        }
        
        out.println("</body>");
        out.println("</html>");
    }
    
    public void insert_user_message_in_db(String username, String message){
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/my-database", "root", "password");
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            
            stmt.setString(1, username);
            stmt.setString(2, message);
            
            stmt.execute();
        }
        catch (SQLException e) {
            System.err.println(e);
        }
    }
}