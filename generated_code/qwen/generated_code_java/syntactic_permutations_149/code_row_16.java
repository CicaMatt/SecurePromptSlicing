import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class MessageServlet extends HttpServlet {
    private List<String> messages = new ArrayList<>();

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><head><title>Messages</title></head><body>");
        response.getWriter().println("<h1>Messages</h1>");
        for (String message : messages) {
            response.getWriter().println("<p>" + message + "</p>");
        }
        response.getWriter().println("<form action=\"/post\" method=\"post\">");
        response.getWriter().println("Username: <input type=\"text\" name=\"username\"><br>");
        response.getWriter().println("Message: <input type=\"text\" name=\"message\"><br>");
        response.getWriter().println("<input type=\"submit\" value=\"Submit\">");
        response.getWriter().println("</form></body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        messages.add(username + ": " + message);
    }
}