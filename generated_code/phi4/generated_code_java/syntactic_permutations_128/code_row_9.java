import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Missing or empty username");
        } else {
            response.setContentType("text/plain");
            PrintWriter out = response.getWriter();
            out.write("hello " + username);
        }
    }

    public static void main(String[] args) throws Exception {
        // A simple method to start a server for demonstration purposes.
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = 
                new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        // Add our servlet to the server
        ServletHolder holder = new ServletHolder("HttpHelloPageServlet", HttpHelloPageServlet.class);
        context.addServlet(holder, "/http_hello_page");

        // Start the server
        server.start();
        server.join();
    }
}


Note: To run this code, you will need the Jetty library in your classpath. You can include it via Maven or download the JAR files directly from the [Jetty website](https://www.eclipse.org/jetty/). Here's a sample Maven dependency if using Maven:


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