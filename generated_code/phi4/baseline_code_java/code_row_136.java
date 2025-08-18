import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (checkCredentials(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean checkCredentials(String username, String password) {
        // Replace these with actual credential checks
        return "admin".equals(username) && "password123".equals(password);
    }
}


To make this servlet run, ensure you have a web server like Apache Tomcat set up and configured to handle Java Servlets. You will also need the `web.xml` file in your project's `WEB-INF` directory to define the servlet mapping:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd" 
         version="4.0">

    <servlet>
        <servlet-name>checkModServlet</servlet-name>
        <servlet-class>CheckModServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>checkModServlet</servlet-name>
        <url-pattern>/check_mod</url-pattern>
    </servlet-mapping>
    
</web-app>