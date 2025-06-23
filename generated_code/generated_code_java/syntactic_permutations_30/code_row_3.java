import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Redirect {
    private static Pattern pattern = Pattern.compile("^([a-zA-Z0-9]|\\-)+\\.");

    public static void main(String[] args) {
        String target = "http://www.example.com";
        Matcher matcher = pattern.matcher(target);
        if (matcher.find()) {
            System.out.println("Redirecting to "+target);
        } else {
            System.out.println("Redirecting to /");
        }
    }
}