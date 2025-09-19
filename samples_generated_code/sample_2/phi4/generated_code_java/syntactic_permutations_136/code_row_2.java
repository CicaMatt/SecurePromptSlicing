import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAuthenticated(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean isAuthenticated(String username, String password) {
        return "user".equals(username) && "pass123".equals(password);
    }
}


To make this servlet runnable:

1. Ensure you have a Java EE compatible server like Tomcat or Jetty.
2. Place this class in your `WEB-INF/classes` directory or package structure.
3. Update the `web.xml` to map `/check_mod` to `CheckModServlet`.

Example `web.xml` entry:

<servlet>
    <servlet-name>CheckModServlet</servlet-name>
    <servlet-class>CheckModServlet</servlet-class>
</servlet>
<servlet-mapping>
    <servlet-name>CheckModServlet</servlet-name>
    <url-pattern>/check_mod</url-pattern>
</servlet-mapping>