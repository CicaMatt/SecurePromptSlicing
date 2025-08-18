import java.util.regex.Pattern;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class RedirectServlet extends HttpServlet {
    private static final Pattern PATTERN = Pattern.compile("^[a-zA-Z0-9-]+\\.");

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target != null && PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}



<!-- web.xml -->
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