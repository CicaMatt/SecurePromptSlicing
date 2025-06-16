import java.io.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

public class Main {
	private static final String HOST = "host";
    private static final int PORT = 465;
    private static final String USERNAME = "username";
    private static final String PASSWORD = "password";
    private static final String MAIL_SUBJECT = "Unsubscribe from mailing list?";
    private static final String MAIL_FROM = "no-reply@host.com";
    private static final String SCRIPT_PATH = "/path/to/script.sh";
    
    public static void main(String[] args) throws Exception {
        Properties properties = new Properties();
        properties.put("mail.smtp.ssl.trust", HOST);
        properties.put("mail.smtp.user", USERNAME);
        properties.put("mail.smtp.host", HOST);
        properties.put("mail.smtp.port", PORT);
        
        Session session = Session.getDefaultInstance(properties, new javax.mail.Authenticator() {
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication(USERNAME, PASSWORD);
            }
        });

        Message message = new MimeMessage(session);
        message.setFrom(new InternetAddress(MAIL_FROM));
        message.setRecipients(Message.RecipientType.TO, InternetAddress.parse("recipient@host.com"));
        message.setSubject(MAIL_SUBJECT);
        message.setText("Hello,\n\nDo you want to unsubscribe from this mailing list?");
        
        Transport transport = session.getTransport();
        transport.connect();
        transport.sendMessage(message, message.getAllRecipients());
        transport.close();
        
        ProcessBuilder builder = new ProcessBuilder("bash", SCRIPT_PATH);
        Process process = builder.start();
        process.waitFor();
        int exitCode = process.exitValue();
        System.out.println(exitCode == 0 ? "1" : "0");
    }
}