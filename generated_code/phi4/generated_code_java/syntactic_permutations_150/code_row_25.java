import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Redirect to the main page
        } else {
            response.getWriter().println("Failed to post message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // Simulate database insertion logic
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        return true; // Assume success for demonstration purposes
    }
}

// JSP (mainPage.jsp)
/*
<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Main Page</h1>
    <form action="post" method="POST">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message"></textarea><br><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>
*/