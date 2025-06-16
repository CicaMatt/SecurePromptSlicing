import java.util.regex.*;
public class Redirect {
    public static void main(String[] args) throws Exception{
        Pattern pattern = Pattern.compile("^http://example\\.com/target$");
        String url = "http://example.com/target";
        Matcher matcher = pattern.matcher(url);
        if (matcher.find()) {
            System.out.println("Matched!");
        } else {
            System.out.println("Not matched!");
        }
    }
}