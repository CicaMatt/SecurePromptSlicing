import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.RequestDispatcher;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("mainPage.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @WebServlet("/display")
    public static class DisplayMessagesServlet extends HttpServlet {

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            List<String> messages = new ArrayList<>();
            
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String sql = "SELECT username, message FROM messages";
                var statement = conn.createStatement();
                var resultSet = statement.executeQuery(sql);
                
                while (resultSet.next()) {
                    String username = resultSet.getString("username");
                    String message = resultSet.getString("message");
                    messages.add(username + ": " + message);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            request.setAttribute("messages", messages);
            RequestDispatcher dispatcher = request.getRequestDispatcher("displayMessages.jsp");
            dispatcher.forward(request, response);
        }
    }
}


To make this code fully functional:

1. Ensure you have a MySQL database set up with the following table:
   
   CREATE TABLE messages (
       id INT AUTO_INCREMENT PRIMARY KEY,
       username VARCHAR(255) NOT NULL,
       message TEXT NOT NULL
   );
   

2. Configure your `DB_URL`, `USER`, and `PASS` variables accordingly.

3. Create two JSP files: `mainPage.jsp` (redirect target after posting a message) and `displayMessages.jsp` (to display messages).

4. Deploy this code in a Java web application server like Apache Tomcat.