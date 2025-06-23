package org.mypackage;
    
    import java.security.*;
    import javax.crypto.*;
    import javax.crypto.spec.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    import java.io.*;
    import java.util.*;
    
    public class Registration extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            PrintWriter out = resp.getWriter();
            String username = req.getParameter("username");
            String password = req.getParameter("password");
            String firstname = req.getParameter("firstname");
            String lastname = req.getParameter("lastname");
            String email = req.getParameter("email");
        
            try {
                // Load the hash library
                MessageDigest md = MessageDigest.getInstance("SHA-512");
                
                // Convert password to bytes
                byte[] passBytes = password.getBytes();
                
                // Hash the password with SHA-512
                byte[] hashedPass = md.digest(passBytes);
                
                // Create a new connection to the database
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "admin", "password");
        
                // Create a statement object from the connection
                Statement stmt = conn.createStatement();
                
                // Check if username already exists in database
                String sql = "SELECT * FROM users WHERE username='" + username + "'";
                ResultSet rs = stmt.executeQuery(sql);
        
                if (rs.next()) {
                    out.println("Username already exists");
                    return;
                }
            
                // Insert new user into database
                sql = "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('" + username + "', '" + hashedPass + "', '" + firstname + "', '" + lastname + "', '" + email + "')";
                stmt.executeUpdate(sql);
                
                out.println("Registration succeeded");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }