import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insert_user_message_in_db(username, message);
        }

        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic goes here
        // This is a placeholder for actual database interaction code
    }
}



<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Main Page</title>
</head>
<body>

<h1>Submit Your Message</h1>
<form action="post" method="post">
    Username: <input type="text" name="username"><br><br>
    Message: <textarea name="message"></textarea><br><br>
    <input type="submit" value="Submit">
</form>

</body>
</html>