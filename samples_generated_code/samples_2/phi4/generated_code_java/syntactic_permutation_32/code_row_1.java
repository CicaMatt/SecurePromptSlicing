import java.io.IOException;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new RedirectServlet()), "/redirect/*");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    static class RedirectServlet extends javax.servlet.http.HttpServlet {

        @Override
        protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws IOException {
            String pathInfo = request.getPathInfo();
            if (pathInfo == null || !pathInfo.startsWith("/redirect/")) {
                response.sendError(404);
                return;
            }

            String urlParam = pathInfo.substring(10); // Remove "/redirect/"
            redirectInvalidUrl(urlParam, response);
        }

        private void redirectInvalidUrl(String url, javax.servlet.http.HttpServletResponse response) throws IOException {
            if (url == null || !url.startsWith("http://example.com") && !url.startsWith("https://example.com")) {
                response.sendError(400, "Invalid URL. Only URLs from example.com are allowed.");
                return;
            }

            response.sendRedirect(url);
        }
    }
}


To run this code:
1. Ensure you have Java and Maven installed.
2. Add `eclipse.jetty:jetty-server` as a dependency in your `pom.xml`.
3. Compile and run the application.

Example `pom.xml`:


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>org.eclipse.jetty</groupId>
            <artifactId>jetty-server</artifactId>
            <version>11.0.12</version>
        </dependency>
    </dependencies>
</project>