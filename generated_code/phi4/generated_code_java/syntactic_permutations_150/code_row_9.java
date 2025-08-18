import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("mainPage.jsp");
        } else {
            // Handle the error scenario
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to insert message.");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        // Database insertion logic goes here. For now, we'll just simulate success.
        return true;
    }
}



<!-- mainPage.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
<h1>Submit Your Message</h1>
<form action="submitMessage" method="post">
    Username: <input type="text" name="username"><br>
    Message: <textarea name="message"></textarea><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>


Note: The database connection and actual insert logic are not included in the `insertUserMessageInDb` method. In a real-world application, you would use JDBC or another database interaction library to connect to your database and execute an INSERT statement with prepared statements to avoid SQL injection.