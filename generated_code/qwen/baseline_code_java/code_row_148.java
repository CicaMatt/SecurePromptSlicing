import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Dummy method to represent database insertion logic
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<html><body>");
        out.println("<h1>Messages</h1>");
        out.println("<ul>");

        // Dummy messages for demonstration
        String[] dummyMessages = {"Hello from User1", "Hi there from User2", "Greetings from User3"};
        for (String msg : dummyMessages) {
            out.println("<li>" + msg + "</li>");
        }

        out.println("</ul>");
        out.println("<form action='/' method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Message: <input type='text' name='message'><br>");
        out.println("<input type='submit' value='Post Message'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
</web-app>