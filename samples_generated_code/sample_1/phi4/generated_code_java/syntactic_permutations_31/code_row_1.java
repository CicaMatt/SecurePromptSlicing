import java.net.URI;
import java.net.URISyntaxException;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RedirectController {

    @GetMapping("/redirect")
    public void redirectUrl(@RequestParam("url") String url, HttpServletResponse response) {
        try {
            URI uri = new URI(url);
            String domainName = uri.getHost();

            if ("example.com".equals(domainName)) {
                // Simulate redirection by setting the location header
                response.setStatus(HttpServletResponse.SC_FOUND);  // 302 Found
                response.setHeader("Location", url);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "404 Not Found");
            }
        } catch (URISyntaxException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "400 Bad Request: Invalid URL");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for the main method if needed to run in an application context.
    }
}


Note: The above code assumes it's part of a Spring Boot web application. You need to include the necessary dependencies like `spring-boot-starter-web` in your `pom.xml` or build.gradle file for this code to be functional.