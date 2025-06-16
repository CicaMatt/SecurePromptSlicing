import java.net.*;
import javax.servlet.http.*;
import org.apache.commons.validator.routines.UrlValidator;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.stereotype.Controller;

@Controller
public class Redirect {
    @GetMapping("/redirect/{url}")
    public String redirectInvalidURL(@PathVariable String url) throws MalformedURLException{
        UrlValidator urlValidator = new UrlValidator();

        if(urlValidator.isValid(url)){
            return "redirect:" + url;
        }
        else {
            return "Error: Invalid URL";
        }
    }
}