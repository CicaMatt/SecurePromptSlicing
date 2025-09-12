import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "User information not found in session.");
            return;
        }

        String userInfo = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;

        response.setContentType("text/plain");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(userInfo);
    }
}


To make this servlet runnable, ensure you have a Java web server like Apache Tomcat configured to deploy the application. Here's an example `web.xml` configuration for older versions of Servlets:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>InfoServlet</servlet-name>
        <servlet-class>InfoServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>InfoServlet</servlet-name>
        <url-pattern>/info</url-pattern>
    </servlet-mapping>
</web-app>
 

For modern servlet applications, you can use the `@WebServlet` annotation as shown in the code to specify URL patterns directly.