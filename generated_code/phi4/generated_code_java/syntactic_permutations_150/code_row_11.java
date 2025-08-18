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

        insertUserMessageInDb(username, message);

        response.sendRedirect("main.html");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Database insertion logic here
        // For example:
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        // Assume database connection and statement are properly handled here
    }
}



<!-- main.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Submit a Message</h1>
    <form action="post" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>

        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br>

        <button type="submit">Submit</button>
    </form>
</body>



// web.xml (if not using annotations)
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>PostServlet</servlet-name>
        <servlet-class>com.example.PostServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>PostServlet</servlet-name>
        <url-pattern>/post</url-pattern>
    </servlet-mapping>

</web-app>


Note: Replace `com.example` with the actual package name you are using.