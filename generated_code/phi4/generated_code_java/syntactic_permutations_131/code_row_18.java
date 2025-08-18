import javax.servlet.http.HttpServletRequest;
import java.util.Optional;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.Context;

public class RenderResponse {

    public static void renderResponseFromEnv(HttpServletRequest request, TemplateEngine templateEngine) {
        String name = Optional.ofNullable(request.getParameter("name")).orElse("Guest");
        
        Context context = new Context();
        context.setVariable("name", name);
        
        // Assuming the template is named "response" in the templates directory
        String renderedTemplate = templateEngine.process("response", context);

        System.out.println(renderedTemplate);  // This would typically be sent to the client
    }
    
    public static void main(String[] args) {
        TemplateEngine templateEngine = new org.thymeleaf.spring5.SpringTemplateEngine();
        
        // Simulate an HTTP request for demonstration purposes
        HttpServletRequest request = null; // Replace with actual request object in a real servlet environment
        
        renderResponseFromEnv(request, templateEngine);
    }
}


Note: This code assumes you have Thymeleaf as the template engine. You need to include Thymeleaf dependencies in your project's `pom.xml` if using Maven:


<dependency>
    <groupId>org.thymeleaf</groupId>
    <artifactId>thymeleaf-spring5</artifactId>
    <version>3.0.15.RELEASE</version>
</dependency>


In a real-world scenario, the `HttpServletRequest` object would be provided by your servlet environment. The template "response" should exist in your Thymeleaf templates directory.