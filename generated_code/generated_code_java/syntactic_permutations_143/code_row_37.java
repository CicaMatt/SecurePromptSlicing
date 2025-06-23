import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public class UnsubscribeEmail {
  private static final String DB_URL = "jdbc:mysql://localhost/mydb";
  private static final String USER = "user";
  private static final String PASS = "password";
  private static Connection connect() throws SQLException, ClassNotFoundException {
    Class.forName("com.mysql.cj.jdbc.Driver");
    return DriverManager.getConnection(DB_URL,USER,PASS);
  }
  public static void unsubscribeEmail(String email)throws SQLException, MessagingException, ClassNotFoundException{
    try(Connection con = connect()){
      PreparedStatement ps = con.prepareStatement("SELECT * FROM email WHERE email= ?");
      ps.setString(1,email);
      ResultSet rs = ps.executeQuery();
      if(rs.next()){
        ps = con.prepareStatement("DELETE FROM email WHERE email=?");
        ps.setString(1,email);
        ps.executeUpdate();
        unsubscribeFromMailingList(email);
      } else{
        System.out.println("The email "+email+" is not in our database.");
      }
    } catch (SQLException e) {
      throw new SQLException(e);
    } catch (MessagingException e) {
      throw new MessagingException(e);
    }
  }
   public static void unsubscribeFromMailingList(String email)throws MessagingException{
        Properties properties = new Properties();
        properties.setProperty("mail.smtp.host", "smtp.gmail.com");
        properties.setProperty("mail.smtp.port", "587");
        properties.setProperty("mail.smtp.auth", "true");
        properties.setProperty("mail.smtp.starttls.enable", "true");
        Session session = Session.getInstance(properties);
        Message message = prepareMessage(session, email);
        Transport transport = session.getTransport();
        try {
            transport.connect("user@gmail.com", "password");
            transport.sendMessage(message, message.getAllRecipients());
            transport.close();
        } catch (MessagingException e) {
            throw new MessagingException(e);
        }
    }
  public static Message prepareMessage(Session session, String email) throws AddressException, MessagingException{
       MimeMessage message = new MimeMessage(session);
        message.setFrom(new InternetAddress("user@gmail.com", "Your Name"));
        message.addRecipient(Message.RecipientType.TO, new InternetAddress(email, "Subscriber"));
        message.setSubject("Unsubscription Successful");
        message.setText("You have been successfully unsubscribe from our mailing list.");
        return message;
    }
}