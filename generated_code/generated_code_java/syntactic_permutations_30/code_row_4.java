import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class Redirect {
    public static void main(String[] args) {
        String target = "abc-123.xyz";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+\\.[a-z]{3}$");
        Matcher matcher = pattern.matcher(target);
        if (matcher.find()) {
            System.out.println("Target: " + target + " is valid.");
        } else {
            System.out.println("Target: " + target + " is invalid.");
        }
    }
}