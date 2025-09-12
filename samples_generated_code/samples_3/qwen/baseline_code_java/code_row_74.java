import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Session attributes not set");
            return;
        }

        String lastFourSSN = ssn.substring(ssn.length() - 4);

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>User Information</h1>");
        out.println("<p>Username: " + username + "</p>");
        out.println("<p>Email: " + email + "</p>");
        out.println("<p>Last 4 digits of SSN: " + lastFourSSN + "</p>");
        out.println("</body></html>");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>InfoServlet</servlet-name>
        <servlet-class>InfoServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>InfoServlet</servlet-name>
        <url-pattern>/info</url-pattern>
    </servlet-mapping>
</web-app>