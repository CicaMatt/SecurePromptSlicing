<details> 
  <summary>Click For Output!</summary>
  
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirect {
    private String targetUrl = "http://www.example.com";
    private Pattern pattern = Pattern.compile("^/images/(.*)$");

    public void process(String request) {
        Matcher matcher = pattern.matcher(request);
        if (matcher.find()) {
            targetUrl = "http://www.example.com/" + matcher.group(1);
        }
    }
}
</details>