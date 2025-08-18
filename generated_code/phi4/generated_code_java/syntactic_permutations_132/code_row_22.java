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


Ensure you have the following `hello.html` in your resources directory (`src/main/resources/`):


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, <%= username %>!</h1>
</body>
</html>


This code sets up a simple Jetty server that listens on port 8080. When you visit `/hello/<username>`, it processes the request and renders `hello.html` with the specified username. Ensure to include the necessary dependencies for Jetty in your project, such as Maven or Gradle configurations.