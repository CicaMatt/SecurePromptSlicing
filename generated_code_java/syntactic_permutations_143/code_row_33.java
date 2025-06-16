import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
public class EmailService extends HttpServlet{
    private List<String> emails = Arrays.asList("user1@example.com", "user2@example.com");

    public void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        String emailParam = request.getParameter("email");
        if (emails.contains(emailParam)) {
            emails.remove(emailParam);
            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("User " + emailParam + " has been unsubscribed.");
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "User not subscribed.");
        }
    }
}