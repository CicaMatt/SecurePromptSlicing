import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("index.html");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
        System.out.println("Inserting message into database for user: " + username);
        System.out.println("Message: " + message);
    }
}

import java.io.*;
public class IndexPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Submit a Message</h2>");
        out.println("<form action='MessageServlet' method='post'>");
        out.println("Username: <input type='text' name='username'><br><br>");
        out.println("Message: <textarea name='message' rows='4' cols='50'></textarea><br><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>IndexPage</servlet-name>
        <servlet-class>IndexPage</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>IndexPage</servlet-name>
        <url-pattern>/index.html</url-pattern>
    </servlet-mapping>
    
    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/MessageServlet</url-pattern>
    </servlet-mapping>
</web-app>