import javax.servlet.*;
import java.io.*;
import javax.servlet.http.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.mail.Authenticator;
import javax.mail.PasswordAuthentication;
import javax.sql.*;
import java.util.Properties;
import java.util.Scanner;

public class LoginPage extends HttpServlet {
    
    private String user_id;
    private String old_email;
    private String new_email;
    private String confirm_password;
    private String connectionUrl = "jdbc:mysql://localhost/webdb";

    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        user_id = req.getParameter("user_id");
        old_email = req.getParameter("old_email");
        new_email = req.getParameter("new_email");
        confirm_password = req.getParameter("confirm_password");
    }
    
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        
        // Check if user is logged in
        if (user_id == null || old_email == null || new_email == null || confirm_password == null) {
            res.sendRedirect("loginPage.jsp");
            return;
        }
        
        // Validate email
        String regex = "^[a-zA-Z0-9._]+@[a-zA-Z0-9.-]+$";
        if (old_email.isEmpty() || !old_email.matches(regex) || !new_email.matches(regex)) {
            res.sendRedirect("loginPage.jsp?error=Invalid email.");
            return;
        }
        
        // Validate password
        regex = "^[a-zA-Z0-9]+$";
        if (confirm_password.isEmpty() || !confirm_password.matches(regex)) {
            res.sendRedirect("loginPage.jsp?error=Invalid confirm password.");
            return;
        }
        
        // Check email exists in database
        try {
            Connection conn = DriverManager.getConnection(connectionUrl, "username", "password");
            Statement stmt = conn.createStatement();
            String query = "SELECT * FROM users WHERE user_id='" + user_id + "' AND old_email='" + old_email + "';";
            ResultSet rs = stmt.executeQuery(query);
            if (rs.next()) {
                // Check confirm password
                String dbConfirmPassword = rs.getString("confirm_password");
                if (!dbConfirmPassword.equals(confirm_password)) {
                    res.sendRedirect("loginPage.jsp?error=Invalid confirm password.");
                    return;
                }
            } else {
                res.sendRedirect("loginPage.jsp?error=Email does not exist in database.");
                return;
            }
        } catch (Exception e) {
            e.printStackTrace();
            res.sendRedirect("loginPage.jsp?error=Database error.");
            return;
        }
        
        // Update email in database
        try {
            Connection conn = DriverManager.getConnection(connectionUrl, "username", "password");
            Statement stmt = conn.createStatement();
            String query = "UPDATE users SET old_email='" + new_email + "' WHERE user_id='" + user_id + "';";
            stmt.executeUpdate(query);
        } catch (Exception e) {
            e.printStackTrace();
            res.sendRedirect("loginPage.jsp?error=Database error.");
            return;
        }
        
        // Send confirmation email
        try {
            Properties properties = new Properties();
            properties.put("mail.smtp.auth", "true");
            properties.put("mail.smtp.starttls.enable", "true");
            properties.put("mail.smtp.host", "smtp.gmail.com");
            properties.put("mail.smtp.port", "587");
            
            Session session = Session.getInstance(properties, new Authenticator() {
                @Override
                protected PasswordAuthentication getPasswordAuthentication() {
                    return new PasswordAuthentication("username@gmail.com", "password");
                }
            });
            
            Message message = prepareMessage(session, user_id);
            Transport.send(message);
        } catch (Exception e) {
            e.printStackTrace();
            res.sendRedirect("loginPage.jsp?error=Email error.");
            return;
        }
        
        // Redirect to login page
        res.sendRedirect("loginPage.jsp");
    }
    
    public Message prepareMessage(Session session, String user_id) {
        try {
            Message message = new MimeMessage(session);
            message.setFrom(new InternetAddress("username@gmail.com"));
            message.setRecipient(Message.RecipientType.TO, new InternetAddress(old_email));
            message.setSubject("Email changed");
            message.setText("Your email has been changed to " + new_email);
            return message;
        } catch (Exception e) {
            e.printStackTrace();
            res.sendRedirect("loginPage.jsp?error=Email error.");
            return null;
        }
    }
}