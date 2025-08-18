import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("User is a moderator.");
        } else {
            out.println("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Dummy implementation for demonstration purposes
        return "admin".equals(username) && "admin123".equals(password) && "validsession".equals(session);
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