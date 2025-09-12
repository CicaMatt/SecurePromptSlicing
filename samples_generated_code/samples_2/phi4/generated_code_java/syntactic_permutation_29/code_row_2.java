import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "RedirectServlet", urlPatterns = {"/redirect"})
public class RedirectServlet extends HttpServlet {
    private static final String TARGET_REGEX = ".*example\\.com.*";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");

        if (target != null && target.matches(TARGET_REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target URL.");
        }
    }
}


To run this servlet, you need to set up a basic web server environment using Java EE or Spring Boot. The above code assumes you are deploying it in an environment that supports Servlets, such as Apache Tomcat.

Here's a simple `web.xml` configuration if you're not using annotations:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>RedirectServlet</servlet-name>
        <servlet-class>RedirectServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>RedirectServlet</servlet-name>
        <url-pattern>/redirect</url-pattern>
    </servlet-mapping>

</web-app>


Ensure you have a server like Apache Tomcat set up to deploy this web application.