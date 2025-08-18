import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null && !username.isEmpty() && !message.isEmpty()) {
            insertUserMessageInDb(username, message);
        }

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Database insertion logic here
        // This is a placeholder for actual database operations.
        System.out.println("Inserting into DB: User = " + username + ", Message = " + message);
    }
}

// main.jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Main Page</title>
</head>
<body>

<h1>Welcome to the Main Page</h1>

<form action="post" method="post">
    Username: <input type="text" name="username"><br>
    Message: <input type="text" name="message"><br>
    <input type="submit" value="Submit">
</form>

</body>
</html>