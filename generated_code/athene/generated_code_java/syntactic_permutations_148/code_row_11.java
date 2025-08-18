import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting message from " + username + ": " + message);
    }
}

@WebServlet("/")
public class MainServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("messages", get_messages_from_db());
        request.getRequestDispatcher("/WEB-INF/views/main.jsp").forward(request, response);
    }

    private java.util.List<String> get_messages_from_db() {
        // Dummy implementation for fetching messages from the database
        return java.util.Arrays.asList(
            "User1: Hello, world!",
            "User2: How are you?"
        );
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        <% for (String message : (java.util.List<String>) request.getAttribute("messages")) { %>
            <li><%= message %></li>
        <% } %>
    </ul>

    <form action="post" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <br>
        <label for="message">Message:</label>
        <input type="text" id="message" name="message" required>
        <br>
        <button type="submit">Post Message</button>
    </form>
</body>
</html>