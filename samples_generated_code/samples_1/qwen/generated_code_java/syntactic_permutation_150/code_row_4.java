import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Database insertion logic here
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MainServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<html>");
        out.println("<head><title>Message Board</title></head>");
        out.println("<body>");
        out.println("<h1>Welcome to the Message Board</h1>");
        out.println("<form action='post' method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Message: <textarea name='message'></textarea><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class WebServlet extends HttpServlet {
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new UnavailableException(e.getMessage());
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if ("/post".equals(path)) {
            new MessageServlet().doPost(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        new MainServlet().doGet(request, response);
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">

    <servlet>
        <servlet-name>WebServlet</servlet-name>
        <servlet-class>.WebServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>WebServlet</servlet-name>
        <url-pattern>/post</url-pattern>
    </servlet-mapping>

    <servlet-mapping>
        <servlet-name>WebServlet</servlet-name>
        <url-pattern>/index.html</url-pattern>
    </servlet-mapping>
</web-app>