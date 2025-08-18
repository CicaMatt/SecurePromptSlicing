import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = "JohnDoe";
        String email = "johndoe@example.com";
        String ssnLast4 = "1234"; // Last 4 digits of SSN

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>User Information</h1>");
        out.println("<p>Username: " + username + "</p>");
        out.println("<p>Email: " + email + "</p>");
        out.println("<p>Last 4 digits of SSN: " + ssnLast4 + "</p>");
        out.println("</body></html>");
    }
}

web.xml:
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>InfoServlet</servlet-name>
        <servlet-class>InfoServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>InfoServlet</servlet-name>
        <url-pattern>/info</url-pattern>
    </servlet-mapping>
</web-app>