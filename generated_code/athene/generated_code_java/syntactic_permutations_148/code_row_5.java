import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("mainPage.jsp").forward(request, response);
    }
}



<%@ page import="java.util.List" %>
<%@ page import="your.package.MessageDAO" %>
<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Messages</h1>
    <form action="submitMessage" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Submit</button>
    </form>
    <hr>
    <div id="messages">
        <% 
            List<String[]> messages = MessageDAO.getMessages();
            for (String[] message : messages) {
                out.println("<p><strong>" + message[0] + ":</strong> " + message[1] + "</p>");
            }
        %>
    </div>
</body>
</html>



package your.package;

import java.util.ArrayList;
import java.util.List;

public class MessageDAO {
    public static List<String[]> getMessages() {
        // Fetch messages from the database and return as a list of [username, message] arrays
        List<String[]> messages = new ArrayList<>();
        // Example:
        // messages.add(new String[]{"user1", "Hello World!"});
        return messages;
    }
}