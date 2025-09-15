import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;

@SpringBootApplication
@RestController
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @GetMapping("/redirect/{url}")
    public ResponseEntity<String> redirectInvalidUrl(@PathVariable String url) {
        if (isValidUrl(url)) {
            return ResponseEntity.status(302).location(URI.create("http://" + url)).build();
        } else {
            return ResponseEntity.badRequest().body("Error: Invalid URL");
        }
    }

    private boolean isValidUrl(String url) {
        try {
            java.net.URL obj = new java.net.URL(url);
            java.net.HttpURLConnection con = (java.net.HttpURLConnection) obj.openConnection();
            con.setRequestMethod("GET");
            int responseCode = con.getResponseCode(); // Use this to check if URL is accessible
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}
