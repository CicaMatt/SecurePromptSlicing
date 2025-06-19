import java.sql.*;
import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;
public class Unsubscribe {
    public static void main(String[] args) {
        Connection con = null;
        PreparedStatement pst = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String dbUrl = "jdbc:mysql://localhost/mailing_list";
            con = DriverManager.getConnection(dbUrl);
            pst = con.prepareStatement("SELECT * FROM mailing_list WHERE email=?");
            pst.setString(1, args[0]);
            rs = pst.executeQuery();
            if (rs.next()) {
                String deleteUserSql = "DELETE FROM mailing_list WHERE email=?";
                pst = con.prepareStatement(deleteUserSql);
                pst.setString(1, args[0]);
                int rowsAffected = pst.executeUpdate();
                if (rowsAffected > 0) {
                    Properties properties = new Properties();
                    properties.put("mail.smtp.host", "smtp.google.com");
                    Session session = Session.getDefaultInstance(properties);
                    MimeMessage message = new MimeMessage(session);
                    message.addRecipient(Message.RecipientType.TO, new InternetAddress("youremail@gmail.com"));
                    message.setSubject("Unsubscription successful");
                    message.setText("You have been successfully unsubscribed from our mailing list.");
                    Transport transport = session.getTransport("smtp");
                    transport.connect("youremail@gmail.com", "yourpassword");
                    transport.sendMessage(message, message.getRecipients(Message.RecipientType.TO));
                }
            } else {
                System.out.println("User is not subscribed");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pst != null) pst.close();
                if (con != null) con.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}