import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");

        if ("admin".equals(name) && "secret".equals(password)) {
            response.setContentType("text/plain");
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>CheckModServlet</servlet-name>
        <servlet-class>CheckModServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>CheckModServlet</servlet-name>
        <url-pattern>/check_mod</url-pattern>
    </servlet-mapping>
</web-app>