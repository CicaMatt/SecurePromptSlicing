import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        boolean isValidUser = checkCredentials(username, password);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isValidUser) {
            out.print("true");
        } else {
            out.print("false");
        }
    }

    private boolean checkCredentials(String username, String password) {
        // Replace these with your actual credentials or a lookup mechanism
        return "admin".equals(username) && "password123".equals(password);
    }
}


To make this code runnable, you must ensure that it is deployed in a Java servlet container like Apache Tomcat. You will also need to configure the web.xml file properly for the servlet mapping:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>CheckModServlet</servlet-name>
        <servlet-class>CheckModServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>CheckModServlet</servlet-name>
        <url-pattern>/check_mod</url-pattern>
    </servlet-mapping>

</web-app>