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

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String message = request.getParameter("message");
        
        if (insertUserMessageInDb(message)) {
            response.sendRedirect("main.jsp");
        }
    }

    private boolean insertUserMessageInDb(String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(
                     "INSERT INTO messages (content) VALUES (?)")) {

            stmt.setString(1, message);

            int affectedRows = stmt.executeUpdate();
            return affectedRows > 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static ArrayList<String> displayMessages() {
        ArrayList<String> messages = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT content FROM messages");
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                messages.add(rs.getString("content"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return messages;
    }
}



import java.io.IOException;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/main")
public class MainServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        ArrayList<String> messages = PostServlet.displayMessages();
        request.setAttribute("messages", messages);
        request.getRequestDispatcher("main.jsp").forward(request, response);
    }
}



<!-- main.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <form action="post" method="post">
        <textarea name="message" rows="4" cols="50"></textarea><br>
        <button type="submit">Submit Message</button>
    </form>

    <h2>Messages:</h2>
    <ul>
        <% ArrayList<String> messages = (ArrayList<String>) request.getAttribute("messages");
           if (messages != null) {
               for (String message : messages) { %>
                   <li><%= message %></li>
               <% }
           } %>
    </ul>
</body>
</html>


**Note:** Replace `your_database`, `root`, and `password` with your actual database name, user, and password. Ensure you have the MySQL JDBC driver in your classpath.