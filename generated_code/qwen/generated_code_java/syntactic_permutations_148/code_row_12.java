import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.List;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy method to simulate database insertion
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = getMessagesFromDb();

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Messages</h1>");
        for (String message : messages) {
            out.println("<p>" + message + "</p>");
        }
        out.println("</body></html>");
    }

    private List<String> getMessagesFromDb() {
        // Dummy method to simulate database retrieval
        return List.of("Message 1", "Message 2", "Message 3");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/post</url-pattern>
    </servlet-mapping>
    <welcome-file-list>
        <welcome-file>index.html</welcome-file>
    </welcome-file-list>
</web-app>



<!-- index.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Message Board</title>
</head>
<body>
    <h1>Post a Message</h1>
    <form action="post" method="post">
        Username: <input type="text" name="username"><br><br>
        Message: <textarea name="message"></textarea><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>