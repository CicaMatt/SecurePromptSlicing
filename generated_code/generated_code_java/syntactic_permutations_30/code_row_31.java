import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Redirect {
    public static void main(String[] args) {
        String target = "https://www.example.com";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9\\-]+\\.[a-z]{2,}$");
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            System.out.println("Redirecting to " + target);
        } else {
            System.out.println("Invalid target: " + target);
        }
    }
}