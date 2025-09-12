import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.setContentType("text/html");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");
                out.println("<h1>User Information</h1>");
                out.println("<p>Username: " + username + "</p>");
                out.println("<p>Email: " + email + "</p>");
                out.println("<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>");
                out.println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing user information in session");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "No active session found");
        }
    }

    public static void main(String[] args) throws ServletException {
        String webappDirLocation = "src/main/webapp/";
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        Context context = tomcat.addWebapp("/", new File(webappDirLocation).getAbsolutePath());
        Servlet servlet = new InfoServlet();
        Tomcat.addServlet(context, "InfoServlet", servlet);
        context.addServletMappingDecoded("/info", "InfoServlet");

        try {
            tomcat.start();
            tomcat.getServer().await();
        } catch (LifecycleException e) {
            throw new ServletException(e);
        }
    }
}

import org.apache.catalina.LifecycleException;
import org.apache.catalina.startup.Tomcat;

import java.io.File;



<!-- pom.xml for Maven project -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>servlet-example</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>

    <dependencies>
        <dependency>
            <groupId>org.apache.tomcat.embed</groupId>
            <artifactId>tomcat-embed-core</artifactId>
            <version>9.0.58</version>
        </dependency>
        <dependency>
            <groupId>javax.servlet</groupId>
            <artifactId>javax.servlet-api</artifactId>
            <version>4.0.1</version>
            <scope>provided</scope>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>1.8</source>
                    <target>1.8</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>