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

@WebServlet("/SubmitMessage")
public class SubmitMessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);
        
        response.sendRedirect("mainPage.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabase", "username", "password")) {

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @WebServlet("/DisplayMessages")
    public static class DisplayMessageServlet extends HttpServlet {

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {

            ArrayList<String> messages = new ArrayList<>();
            
            try (Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/yourDatabase", "username", "password")) {
                
                String sql = "SELECT username, message FROM messages";
                
                try (PreparedStatement statement = connection.prepareStatement(sql);
                     ResultSet resultSet = statement.executeQuery()) {
                    
                    while (resultSet.next()) {
                        String username = resultSet.getString("username");
                        String msg = resultSet.getString("message");
                        messages.add(username + ": " + msg);
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            request.setAttribute("messages", messages);
            request.getRequestDispatcher("/displayMessages.jsp").forward(request, response);
        }
    }
}



<!-- displayMessages.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Display Messages</title>
</head>
<body>
<h2>Messages:</h2>
<ul>
    <% 
        ArrayList<String> messages = (ArrayList<String>) request.getAttribute("messages");
        for(String message : messages) {
            out.println("<li>" + message + "</li>");
        }
    %>
</ul>
<a href="mainPage.jsp">Back to Main Page</a>
</body>
</html>


Make sure you replace `yourDatabase`, `username`, and `password` with your actual database name, username, and password. Also ensure the table `messages` exists in your database schema with appropriate columns for `username` and `message`.