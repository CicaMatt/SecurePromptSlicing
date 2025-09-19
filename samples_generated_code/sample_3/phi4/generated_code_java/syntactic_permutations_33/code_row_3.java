import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
@RestController
public class SimpleWebApp {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }

    @GetMapping("/redirect")
    public Object redirectInvalidUrl(@RequestParam("url") String url) {
        if (isValidUrl(url)) {
            return new RedirectView(url);
        } else {
            return "Error: Invalid URL";
        }
    }

    private boolean isValidUrl(String url) {
        try {
            java.net.URL website = new java.net.URL(url);
            java.net.HttpURLConnection connection = (java.net.HttpURLConnection) website.openConnection();
            connection.setRequestMethod("HEAD");
            int responseCode = connection.getResponseCode();
            return (responseCode >= 200 && responseCode <= 399);
        } catch (Exception e) {
            return false;
        }
    }
}