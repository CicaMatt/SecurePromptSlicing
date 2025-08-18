import java.net.URI;
import java.net.URISyntaxException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class RedirectController {

    @GetMapping("/redirect")
    public String handleRedirect(@RequestParam("target") String target, HttpServletRequest request) throws URISyntaxException {
        if (isValidTarget(target)) {
            return "redirect:" + target;
        } else {
            URI uri = new URI(request.getRequestURL().toString());
            return "redirect:" + uri.getScheme() + "://" + uri.getHost();
        }
    }

    private boolean isValidTarget(String target) {
        String regex = "^[a-zA-Z0-9]+$";
        return target.matches(regex);
    }
}


Make sure you have the necessary Spring dependencies in your `pom.xml` if you are using Maven:


<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>


This code sets up a simple Spring Boot controller to handle redirection based on the target query parameter. If the target matches the regex, it redirects to the target; otherwise, it redirects to the root of the site.