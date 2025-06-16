import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import java.util.Properties;
import java.sql.*;

public class UnsubscribeService implements HttpHandler {
    @Override
    public void handle(HttpExchange httpExchange) throws IOException {
        String email = httpExchange.getRequestURI().getQuery().split("email=")[1];
        if (email == "test@gmail.com"){
            deleteUserFromDatabase(email);
            unsubscribeUserFromMailingList(email);
            respondWithMessage(httpExchange, "Unsubscribed successfully");
        } else {
            respondWithMessage(httpExchange, "You are not subscribed.");
        }
    }

    private void deleteUserFromDatabase(String email) throws SQLException {
        String dbUrl = "jdbc:mysql://localhost/";
        String dbName = "user_info";
        Connection conn = DriverManager.getConnection(dbUrl+dbName);
        Statement stmt = conn.createStatement();
        String sql = "DELETE FROM users WHERE email = '"+email+"'";
        stmt.executeUpdate(sql);
    }

    private void unsubscribeUserFromMailingList(String email) throws MessagingException {
        Properties properties = new Properties();
        properties.setProperty("mail.transport.protocol", "smtp");
        properties.setProperty("mail.smtp.port", "25");
        Session session = Session.getDefaultInstance(properties);
        Message message = new MimeMessage(session);
        message.setFrom(new InternetAddress("admin@example.com"));
        message.setRecipient(Message.RecipientType.TO, new InternetAddress(email));
        Transport transport = session.getTransport();
        transport.connect();
        transport.sendMessage(message);
    }

    private void respondWithMessage(HttpExchange httpExchange, String message) throws IOException {
        OutputStream outputStream = httpExchange.getResponseBody();
        httpExchange.getResponseHeaders().add("Content-Type", "text/html;charset=utf-8");
        outputStream.write("<h1>".getBytes());
        outputStream.write(message.getBytes());
        outputStream.write("</h1>".getBytes());
    }
}