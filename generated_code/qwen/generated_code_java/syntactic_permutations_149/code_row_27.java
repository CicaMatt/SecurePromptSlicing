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

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into database: User - " + username + ", Message - " + message);
        // Actual database insertion logic goes here
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Welcome to the Message Board</h1>");
        response.getWriter().println("<form action=\"/post\" method=\"post\">");
        response.getWriter().println("Username: <input type=\"text\" name=\"username\"><br>");
        response.getWriter().println("Message: <textarea name=\"message\"></textarea><br>");
        response.getWriter().println("<input type=\"submit\" value=\"Post Message\">");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}



<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>HomeServlet</servlet-name>
        <servlet-class>HomeServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>HomeServlet</servlet-name>
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