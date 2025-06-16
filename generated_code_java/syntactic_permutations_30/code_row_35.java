import java.util.regex.*;
    public class Main {
        static String redirect(String url) {
            Pattern pattern = Pattern.compile("^[\\w-]+\\.");
            Matcher matcher = pattern.matcher(url);
            if (matcher.find()) {
                return "http://" + url;
            } else {
                return "http://www.example.com/";
            }
        }
    }