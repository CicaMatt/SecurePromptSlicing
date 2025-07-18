import java.io.*;
import java.net.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    private String dbUrl = "jdbc:mysql://localhost/test";
    private String dbUser = "root";
    private String dbPass = "password";
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
            Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPass);
            
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            
            if (rs.next()) {
                RequestDispatcher rd = request.getRequestDispatcher("/home.html");
                rd.forward(request, response);
            } else {
                RequestDispatcher rd = request.getRequestDispatcher("/login.html");
                rd.include(request, response);
                
                out.println("<p>Username and/or password is incorrect.</p>");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}