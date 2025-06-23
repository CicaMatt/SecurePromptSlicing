import java.util.regex.*;
public class Redirection{
    public static void main(String[] args) {
        String regex = "^[a-zA-Z0-9]+(?:[-][a-zA-Z0-9]+)+(?:\\.[a-zA-Z0-9]+)+$";
        Pattern pattern = Pattern.compile(regex);
        String target = "https://www.example.com/path/to/file";
        Matcher matcher = pattern.matcher(target);
        if (matcher.find()) {
            System.out.println("Redirecting to " + target);
        } else {
            System.out.println("Redirecting to https://www.example.com");
        }
    }
}