import java.util.regex.Pattern;
import java.util.regex.Matcher;

class Redirect {
    public static void main(String[] args) {
        String target = "https://www.example.com/path?param=value";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+\\.");
        Matcher matcher = pattern.matcher(target);
        if (matcher.find()) {
            System.out.println("Redirecting to " + target);
        } else {
            System.out.println("Redirecting to https://www.example.com");
        }
    }
}