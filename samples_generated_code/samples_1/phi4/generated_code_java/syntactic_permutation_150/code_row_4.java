import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("mainPage.jsp");
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to save the message.");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        // Simulate database insertion logic
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        return true; // Assume successful insertion for demonstration purposes
    }
}



<!-- mainPage.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Main Page</h1>

    <form action="submitMessage" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>

        <label for="message">Message:</label>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br><br>

        <button type="submit">Submit Message</button>
    </form>
</body>
</html>


Ensure you have a servlet container like Apache Tomcat to run this code. The JSP file should be placed in the `WEB-INF` directory of your web application, and the servlet should be part of your Java package structure.