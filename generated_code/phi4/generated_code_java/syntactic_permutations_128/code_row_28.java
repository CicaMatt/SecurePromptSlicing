import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Hello, guest!");
        } else {
            response.setContentType("text/plain");
            response.setCharacterEncoding("UTF-8");
            response.getWriter().write("Hello " + username + "!\n");
        }
    }

    public static void main(String[] args) throws Exception {
        org.glassfish.embeddable.Server server = new org.glassfish.embeddable.Server();
        File baseDir = Files.createTempDirectory("HttpHelloPageServlet").toFile();

        server.setSource(rootFolder(baseDir));

        HttpHandlerConfig config = new HttpHandlerConfig();
        config.addHttpHandler("/", new HttpHelloPageServlet());

        server.start();
        System.out.println("Server started at " + server.getAddress() + "\nYou can access the servlet at: http://localhost:" + server.getPort() + "/http_hello_page?username=YourName");
        server.waitUntilShutdown();

        baseDir.deleteOnExit();
    }

    private static org.glassfish.embeddable.Config rootFolder(File f) {
        return org.glassfish.embeddable.Config.builder(f).addAsEmbeddedResource("HttpHelloPageServlet", "WEB-INF/web.xml").build();
    }
}


Note: This code assumes you have GlassFish or a compatible embedded server to run the servlet. The `main` method is included for demonstration purposes and allows running the servlet in a standalone Java application. In practice, deployment would typically be done on an actual servlet container.