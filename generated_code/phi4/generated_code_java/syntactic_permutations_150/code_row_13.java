import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming mainPage.jsp is your main page
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        
        // Here you would have logic to connect to a database and insert the user's message.
        // For example, using JDBC or an ORM like Hibernate.
    }
}



<!-- Assuming this is part of mainPage.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Message Board!</h1>
    <form action="post" method="POST">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username" required><br>
        
        <label for="message">Message:</label><br>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br>

        <input type="submit" value="Submit Message">
    </form>
</body>
</html>


Note: Make sure you have a servlet container like Apache Tomcat set up to run this code. The `mainPage.jsp` should be deployed in the appropriate directory of your web application.