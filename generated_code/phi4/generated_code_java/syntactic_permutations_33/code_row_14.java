import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String urlParam = req.getParameter("url");
        if (urlParam != null && isValidUrl(urlParam)) {
            resp.sendRedirect(urlParam);
        } else {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL provided.");
        }
    }

    private boolean isValidUrl(String url) {
        // Basic validation for well-formed URLs
        try {
            new java.net.URL(url).toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}




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



// Main class for running the server (Assuming you are using an embedded server like Tomcat)
import org.apache.catalina.startup.Tomcat;

public class WebAppRunner {
    public static void main(String[] args) throws Exception {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        String webappDirLocation = System.getProperty("java.io.tmpdir") + "/webapps";
        Context ctx = tomcat.addWebapp("/", webappDirLocation);

        tomcat.start();
        tomcat.getServer().await();
    }
}
