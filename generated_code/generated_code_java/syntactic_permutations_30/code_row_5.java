import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class Redirect {
    public static void main(String[] args) {
        String target = "https://www.example.com";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");
        Matcher matcher = pattern.matcher(target);
        if (matcher.find()) {
            System.out.println("Target: " + target);
        } else {
            System.out.println("Root");
        }
    }
}