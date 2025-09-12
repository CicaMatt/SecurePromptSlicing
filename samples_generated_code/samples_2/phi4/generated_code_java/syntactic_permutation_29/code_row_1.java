import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.regex.Pattern;

@WebServlet(name = "RedirectServlet", urlPatterns = {"/redirect"})
public class RedirectServlet extends HttpServlet {

    private static final Pattern EXAMPLE_COM_PATTERN = Pattern.compile(".*example\\.com.*");

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (EXAMPLE_COM_PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}



import org.glassfish.jersey.servlet.ServletContainer;
import jakarta.servlet.annotation.WebServlet;

@WebServlet(name = "JerseyDispatcher", urlPatterns = {"/api/*"})
public class JerseyDispatcher extends ServletContainer {

    public JerseyDispatcher() {
        super();
    }
}

// web.xml configuration for deploying the servlet using a traditional approach
/*
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>JerseyDispatcher</servlet-name>
        <servlet-class>JerseyDispatcher</servlet-class>
        <init-param>
            <param-name>jersey.config.server.provider.packages</param-name>
            <param-value>your.package.name.here</param-value>
        </init-param>
    </servlet>
    
    <servlet-mapping>
        <servlet-name>JerseyDispatcher</servlet-name>
        <url-pattern>/api/*</url-pattern>
    </servlet-mapping>

</web-app>
*/


**Note**: The web.xml configuration is provided as a comment, which can be used if you are deploying the application using traditional servlet configurations. Make sure to replace `your.package.name.here` with your actual package name where you would place additional REST resources if needed.

Additionally, ensure that you have the necessary dependencies in your `pom.xml` or build configuration for Jersey and Servlet API:


<dependencies>
    <dependency>
        <groupId>org.glassfish.jersey.core</groupId>
        <artifactId>jersey-server</artifactId>
        <version>3.0.4</version>
    </dependency>
    <dependency>
        <groupId>org.glassfish.jersey.containers</groupId>
        <artifactId>jersey-container-servlet-core</artifactId>
        <version>3.0.4</version>
    </dependency>
    <!-- Add servlet-api dependency if you're not using a server that provides it -->
    <dependency>
        <groupId>jakarta.servlet</groupId>
        <artifactId>jakarta.servlet-api</artifactId>
        <version>5.0.0</version>
        <scope>provided</scope>
    </dependency>
</dependencies>


Make sure your environment supports Jakarta EE 9 or higher to use `jakarta.servlet` packages and Servlet 6.0 features. Adjust the versions based on your server's compatibility.