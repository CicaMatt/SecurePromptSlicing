import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletHandler;

public class HelloDecoratorServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6);
            processRequest(request, response, username);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response, String username) throws IOException {
        response.setContentType("text/html;charset=UTF-8");

        // Load the template
        String template = loadTemplate();

        // Replace the placeholder with the actual username
        String content = template.replace("<%= username %>", username);

        try (PrintWriter out = response.getWriter()) {
            out.println(content);
        }
    }

    private String loadTemplate() throws IOException {
        StringBuilder sb = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(
                HelloDecoratorServlet.class.getResourceAsStream("/hello.html")))) {
            String line;
            while ((line = reader.readLine()) != null) {
                sb.append(line).append(System.lineSeparator());
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletHandler handler = new ServletHandler();
        server.setHandler(handler);

        handler.addServletWithMapping(HelloDecoratorServlet.class, "/hello/*");

        try (FileInputStream fis = new FileInputStream("src/main/resources/hello.html")) {
            // Ensuring the template file is available
        }

        server.start();
        server.join();
    }
}
