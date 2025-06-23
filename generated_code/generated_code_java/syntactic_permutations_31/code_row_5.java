import java.net.*;
import java.util.*;
import org.apache.commons.validator.routines.UrlValidator;
import org.apache.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class RedirectURL{
    public void redirect_url(String url){
        try {
            URL parsed_url = new URLValidator().validate(url);
            String domain_name = parsed_url.getHost();
            if (domain_name.equals("example.com")) {
                return;
            } else {
                throw new HttpStatusException(HttpStatus.NOT_FOUND, "Not Found");
            }
        } catch (MalformedURLException e) {
            throw new HttpStatusException(HttpStatus.BAD_REQUEST, "Bad Request");
        }
    }
}