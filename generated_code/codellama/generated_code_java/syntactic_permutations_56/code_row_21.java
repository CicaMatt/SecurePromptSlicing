import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String oldEmail = request.getParameter("oldEmail");
        String newEmail = request.getParameter("newEmail");
        String confirmPassword = request.getParameter("confirmPassword");
        if (oldEmail != null && newEmail != null && confirmPassword != null) {
            // check if user is logged in
            HttpSession session = request.getSession(false);
            if (session == null || session.getAttribute("user") == null) {
                response.sendRedirect("login");
                return;
            }
            User user = (User) session.getAttribute("user");
            // check if oldEmail matches user's email
            if (!oldEmail.equals(user.getEmail())) {
                request.setAttribute("error", "Invalid old email address.");
                RequestDispatcher view = request.getRequestDispatcher("/WEB-INF/login.jsp");
                view.forward(request, response);
                return;
            }
            // check if newEmail matches user's email
            if (newEmail.equals(user.getEmail())) {
                request.setAttribute("error", "New email address cannot be the same as your current email address.");
                RequestDispatcher view = request.getRequestDispatcher("/WEB-INF/login.jsp");
                view.forward(request, response);
                return;
            }
            // check if confirmPassword matches user's password
            if (!confirmPassword.equals(user.getPassword())) {
                request.setAttribute("error", "Invalid password.");
                RequestDispatcher view = request.getRequestDispatcher("/WEB-INF/login.jsp");
                view.forward(request, response);
                return;
            }
            // send email to newEmail with verification link
            String verificationLink = "https://www.example.com/verify?email=" + URLEncoder.encode(newEmail, "UTF-8") + "&verificationCode=" + UUID.randomUUID().toString();
            sendVerificationEmail(newEmail, verificationLink);
            request.setAttribute("success", "A verification email has been sent to your new email address.");
            RequestDispatcher view = request.getRequestDispatcher("/WEB-INF/login.jsp");
            view.forward(request, response);
        } else {
            String errorMessage = "Invalid input.";
            if (oldEmail == null) {
                errorMessage += " Old email address is required.";
            }
            if (newEmail == null) {
                errorMessage += " New email address is required.";
            }
            if (confirmPassword == null) {
                errorMessage += " Confirm password is required.";
            }
            request.setAttribute("error", errorMessage);
            RequestDispatcher view = request.getRequestDispatcher("/WEB-INF/login.jsp");
            view.forward(request, response);
        }
    }
    private void sendVerificationEmail(String newEmail, String verificationLink) {
        // create Session object to connect to Gmail SMTP
        Properties props = new Properties();
        props.put("mail.smtp.host", "smtp.gmail.com");
        props.put("mail.smtp.port", "587");
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.starttls.enable", "true");
        Session session = Session.getInstance(props, new javax.mail.Authenticator() {
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication("<GMAIL_EMAIL_ADDRESS>", "<GMAIL_PASSWORD>");
            }
        });
        try {
            // create MimeMessage object
            Message message = new MimeMessage(session);
            message.setFrom(new InternetAddress("noreply@example.com", "Example"));
            message.addRecipient(Message.RecipientType.TO, new InternetAddress(newEmail));
            message.setSubject("Verify Your Email");
            // create message body part
            BodyPart messageBodyPart = new MimeBodyPart();
            messageBodyPart.setText("Dear user,\n\nPlease click the link below to verify your email address:\n" + verificationLink + "\n\nThank you,\nExample");
            Multipart multipart = new MimeMultipart();
            multipart.addBodyPart(messageBodyPart);
            message.setContent(multipart);
            // send message
            Transport transport = session.getTransport("smtp");
            transport.connect("<GMAIL_EMAIL_ADDRESS>", "<GMAIL_PASSWORD>");
            transport.sendMessage(message, message.getAllRecipients());
            transport.close();
        } catch (MessagingException e) {
            throw new RuntimeException(e);
        }
    }
}