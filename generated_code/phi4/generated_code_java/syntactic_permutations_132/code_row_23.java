import java.io.*;
import java.nio.file.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && !pathInfo.isEmpty() && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6); // Remove /hello/
            
            Path templatePath = Paths.get("src/main/resources/hello.html");
            if (!Files.exists(templatePath)) {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
                return;
            }
            
            String content = new String(Files.readAllBytes(templatePath));
            content = content.replace("${username}", username);

            response.setContentType("text/html");
            response.getWriter().write(content);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    public static void main(String[] args) throws Exception {
        // A simple server to test the servlet
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new HelloServlet()), "/hello/*");

        server.start();
        server.join();
    }
}


Note: You need to have Jetty as a dependency in your project for this code to run:


<dependency>
    <groupId>org.eclipse.jetty</groupId>
    <artifactId>jetty-server</artifactId>
    <version>11.0.14</version>
</dependency>

<dependency>
    <groupId>org.eclipse.jetty</groupId>
    <artifactId>jetty-servlet</artifactId>
    <version>11.0.14</version>
</dependency>


Ensure that the `hello.html` file is placed in `src/main/resources/` with content like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>