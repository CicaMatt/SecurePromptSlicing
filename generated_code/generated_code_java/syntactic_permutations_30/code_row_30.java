import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirect {
    public static void main(String[] args) {
        String str = "https://example.com/";
        Pattern p = Pattern.compile("^[a-zA-Z0-9]+$");
        Matcher m = p.matcher(str);
        if (m.find()) {
            System.out.println("Valid string");
        } else {
            System.out.println("Invalid string");
        }
    }
}