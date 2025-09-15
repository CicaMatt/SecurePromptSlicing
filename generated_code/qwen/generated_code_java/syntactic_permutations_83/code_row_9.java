import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class NameCheckerServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        if (name != null && !name.trim().isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.setContentType("text/plain");
            response.getWriter().write("Name field is missing or empty.");
        }
    }
}



<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>NameCheckerServlet</servlet-name>
        <servlet-class>NameCheckerServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>NameCheckerServlet</servlet-name>
        <url-pattern>/checkName</url-pattern>
    </servlet-mapping>
</web-app>



import java.io.File;
import org.apache.catalina.LifecycleException;
import org.apache.catalina.WebResourceRoot;
import org.apache.catalina.core.StandardContext;
import org.apache.catalina.startup.Tomcat;

public class WebAppRunner {
    public static void main(String[] args) throws LifecycleException {
        String webappDirLocation = "src/main/webapp/";
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        StandardContext ctx = (StandardContext) tomcat.addWebapp("", new File(webappDirLocation).getAbsolutePath());
        WebResourceRoot resources = new WebResourceRoot(ctx, "/WEB-INF/classes",
                new File("target/classes").getAbsolutePath());
        ctx.setResources(resources);

        tomcat.start();
        tomcat.getServer().await();
    }
}
