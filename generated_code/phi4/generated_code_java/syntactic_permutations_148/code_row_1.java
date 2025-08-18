import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Redirect to main page
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String dbUser = "yourDbUser";
        String dbPassword = "yourDbPassword";

        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, username);
            stmt.setString(2, message);

            int rowsAffected = stmt.executeUpdate();
            return rowsAffected > 0;

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

}

// Another Servlet to display messages
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/displayMessages")
public class DisplayMessagesServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        ArrayList<String[]> messages = getMessagesFromDatabase();

        request.setAttribute("messages", messages);
        request.getRequestDispatcher("mainPage.jsp").forward(request, response); // Forward to JSP page
    }

    private ArrayList<String[]> getMessagesFromDatabase() {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String dbUser = "yourDbUser";
        String dbPassword = "yourDbPassword";

        String sql = "SELECT username, message FROM messages";
        ArrayList<String[]> messages = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
             PreparedStatement stmt = conn.prepareStatement(sql);
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                String[] messageData = { rs.getString("username"), rs.getString("message") };
                messages.add(messageData);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return messages;
    }
}


In this code, you'll also need to create a `mainPage.jsp` file that will handle the display of messages. Here's an example:


<%@ page import="java.util.ArrayList" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Messages</h1>
    <form action="post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Post</button>
    </form>

    <ul>
        <% 
            ArrayList<String[]> messages = (ArrayList<String[]>) request.getAttribute("messages");
            if (messages != null) {
                for (String[] messageData : messages) {
                    out.println("<li><strong>" + messageData[0] + ":</strong> " + messageData[1] + "</li>");
                }
            }
        %>
    </ul>

</body>
</html>


Make sure to replace `yourDatabase`, `yourDbUser`, and `yourDbPassword` with your actual database name, user, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.