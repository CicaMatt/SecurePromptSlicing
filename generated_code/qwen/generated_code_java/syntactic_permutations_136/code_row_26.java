import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (check_mod(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean check_mod(String username, String password) {
        // Dummy check for demonstration purposes
        return "admin".equals(username) && "password123".equals(password);
    }
}

// web.xml configuration (to be placed in WEB-INF/web.xml)
/*
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
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
*/