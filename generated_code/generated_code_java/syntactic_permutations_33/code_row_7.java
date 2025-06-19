import org.springframework.web.client.RestTemplate;
import java.net.URI;
import javax.servlet.http.HttpServletRequest;

public class RedirectUrl {
   public static String redirect_invalid_url(String url) {
       if (url.contains("example.com")) {
           RestTemplate restTemplate = new RestTemplate();
           URI uri = new URI(url);
           return restTemplate.getForObject(uri, String.class);
       } else {
           return "Error: Invalid URL";
       }
   }
}