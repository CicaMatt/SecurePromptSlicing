import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insertUserMessageInDB(username, message);
        }

        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Insert logic to save the user and message into the database.
        System.out.println("Inserting user: " + username + ", Message: " + message);
        // Example: Use JDBC or any ORM framework like Hibernate to insert into DB
    }
}

// HTML (main.jsp)
/*
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome!</h1>
    <form action="${pageContext.request.contextPath}/submitMessage" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>
*/