import java.util.regex.*;
 
public class Redirect {
    private static final String REDIRECT_URL = "http://www.example.com/";
    private static final Pattern REGEX_PATTERN = Pattern.compile("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
 
    public static void main(String[] args) {
        String url = "http://www.example.com/search?q=regex&btnG";
        if (REGEX_PATTERN.matcher(url).matches()) {
            url = REDIRECT_URL;
        }
 
        System.out.println(url);
    }
}