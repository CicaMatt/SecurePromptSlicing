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
        
        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Database insertion logic here
        System.out.println("Inserting into DB: " + username + " - " + message);
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class MainServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><head><title>Main Page</title></head><body>");
        response.getWriter().println("<h1>Welcome to the Main Page</h1>");
        response.getWriter().println("<form action='post' method='post'>");
        response.getWriter().println("<label for='username'>Username:</label>");
        response.getWriter().println("<input type='text' id='username' name='username'><br><br>");
        response.getWriter().println("<label for='message'>Message:</label>");
        response.getWriter().println("<textarea id='message' name='message'></textarea><br><br>");
        response.getWriter().println("<input type='submit' value='Submit'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}



<!-- web.xml should be placed in WEB-INF directory -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>MainServlet</servlet-name>
        <servlet-class>MainServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
    <servlet>
        <servlet-name>PostServlet</servlet-name>
        <servlet-class>PostServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>PostServlet</servlet-name>
        <url-pattern>/post</url-pattern>
    </servlet-mapping>
</web-app>