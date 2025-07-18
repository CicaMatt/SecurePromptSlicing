import java.util.regex.*;
 
public class RegExpExample {
    public static void main(String[] args) {
        String target = "http://www.example.com/some-page";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+\\.");
        Matcher matcher = pattern.matcher(target);
 
        if (matcher.find()) {
            System.out.println("Match found");
        } else {
            System.out.println("Match not found");
        }
    }
}