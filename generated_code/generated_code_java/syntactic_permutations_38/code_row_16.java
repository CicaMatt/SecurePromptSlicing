import java.io.*;
import java.net.*;  // Importing required packages
import java.sql.*;  
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
     public void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException, ServletException {
        res.setContentType("text/html");
        PrintWriter out = res.getWriter();
        
        String name = req.getParameter("username");
        String pass = req.getParameter("password");
       
        try {
            // Database connection
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root","123456789");
            
            Statement stmt = con.createStatement();
            ResultSet rs;
            
            // Query to check if the user exists
            String query = "SELECT * FROM users WHERE username = '" + name + "' AND password = '" + pass + "';"; 
            rs = stmt.executeQuery(query);
            
            if (rs.next()) {
                RequestDispatcher rd = req.getRequestDispatcher("dashboard.html");
                out.println("<p>Welcome, " + name + "</p>");
                rd.forward(req, res);
            } else {
                RequestDispatcher rd = req.getRequestDispatcher("login.html");
                out.println("<p>Incorrect username or password</p>");
                rd.include(req, res);
            }
            
        } catch (Exception e) {
            e.printStackTrace();
        }
        
    }
}