package com.subscription;
import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.*;
import java.sql.*;
import org.apache.commons.codec.digest.DigestUtils;
@RestController
public class SubscriptionService {
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
    static final String DB_URL = "jdbc:mysql://localhost/subscribers";
    @GetMapping("/unsubscribe")
    public void unsubscribe(@RequestParam(value="email", defaultValue="") String email, HttpServletResponse response) throws Exception {
        if (email == null || email.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }
        Connection conn = null;
        Statement stmt = null;
        try{
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DB_URL, "root", "password");
            String query = "SELECT email FROM subscribers WHERE email='" + email + "'";
            stmt = conn.createStatement();  
            ResultSet rs = stmt.executeQuery(query); 
            if (!rs.next()) {
                response.getWriter().println("Email not found");
            } else {
                query = "DELETE FROM subscribers WHERE email='" + email + "'";
                stmt.executeUpdate(query);
                response.sendRedirect("/unsubscribed");
            }
        } catch (SQLException se) {
            se.printStackTrace();
        } finally {
            try {
                if (stmt != null)
                    conn.close();
            } catch (SQLException se) {
            }
            try {
                if (conn != null)
                    conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }
}
