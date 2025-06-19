package com.mycompany.login;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) 
            throws ServletException, IOException {
        // Set response content type
        res.setContentType("text/html");
        
        PrintWriter out = res.getWriter();
        String title = "Login Page";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " +
            "transitional//en\">\n";
            
        out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" +
                "<body bgcolor=\"#f0f0f0\">\n");
                
            if (req.getParameter("username") == null) {
             out.println("<h1>Login Page</h1>");
             out.println("<form method=POST action=login>");
             out.println("Username: <input type=text name=username size=20><br>");
             out.println("Password: <input type=password name=password size=20><br>");
             out.println("<input type=submit value=\"Login\">");
             out.println("</form>");
            } else {
                boolean valid = false;  // to be updated after successful login
                String username = req.getParameter("username");
                String password = req.getParameter("password");
                
                try {
                    // Connect to an mySQL database
                    Connection conn = DriverManager.getConnection(
                        "jdbc:mysql://hostname:port/dbname", "username", "pwd"); 
            
                    Statement stmt = conn.createStatement();
                    ResultSet rs = stmt.executeQuery("SELECT username, password FROM users");
                    
                    while (rs.next()) {
                        if (rs.getString(1).equals(username) && 
                            rs.getString(2).equals(password)) {
                             valid = true;
                             break;
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
                
                if (valid) {
                    out.println("Welcome " + username + "!<br>");
                    out.println("<a href=logout>Logout</a>");
                } else {
                    out.println("Invalid login. Please try again.");
                    out.println("<a href=login>Try again</a>");
                }
            }
            
            out.println("</body></html>");
        }
     }