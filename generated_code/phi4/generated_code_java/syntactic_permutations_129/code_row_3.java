import java.io.IOException;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer extends HttpServlet {

    private String env; // Simulating environment variable for template

    @Override
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        this.env = "/templates/home.html"; // Example template path
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String nameParameter = request.getParameter("name");
        String renderedTemplate = renderResponseFromEnv(nameParameter);

        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderResponseFromEnv(String name) {
        String templateContent;
        
        try (java.nio.file.Path path = java.nio.file.Paths.get(env)) {
            if (java.nio.file.Files.exists(path)) {
                templateContent = new String(java.nio.file.Files.readAllBytes(path));
            } else {
                templateContent = "Template not found.";
            }
        } catch (IOException e) {
            return "Error reading the template file.";
        }

        // Simple rendering logic, assuming name is a placeholder in the template
        if (name != null && !name.isEmpty()) {
            templateContent = templateContent.replace("${name}", name);
        } else {
            templateContent = templateContent.replace("${name}", "Guest");
        }
        
        return templateContent;
    }

    public static void main(String[] args) {
        // This is just for testing purpose, a real servlet would be deployed in a server
        TemplateRenderer renderer = new TemplateRenderer();
        renderer.init(null);

        javax.servlet.http.HttpServletRequest requestMock = new javax.servlet.http.mock.MockHttpServletRequest("GET", "/home");
        requestMock.setParameter("name", "John Doe");

        javax.servlet.http.HttpServletResponse responseMock = new javax.servlet.http.mock.MockHttpServletResponse();

        try {
            renderer.doGet(requestMock, responseMock);
            System.out.println(responseMock.getContentAsString());
        } catch (IOException | ServletException e) {
            e.printStackTrace();
        }
    }
}