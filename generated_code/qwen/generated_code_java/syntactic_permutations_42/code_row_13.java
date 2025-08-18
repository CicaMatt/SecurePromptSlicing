import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class UserInfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null &&
                session.getAttribute("email") != null && session.getAttribute("ssn") != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            response.setContentType("text/plain");
            response.getWriter().write(String.format("Username: %s%nEmail: %s%nSSN: %s", username, email, ssn));
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found or incomplete user information.");
        }
    }
}



<!-- WEB-INF/web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>UserInfoServlet</servlet-name>
        <servlet-class>UserInfoServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>UserInfoServlet</servlet-name>
        <url-pattern>/info</url-pattern>
    </servlet-mapping>
    
</web-app>