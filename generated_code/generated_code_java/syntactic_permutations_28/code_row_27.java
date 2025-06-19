import java.util.regex.*;
public class Redirect {
    private static final String TARGET_REGEX = "http://www\\.example\\.com";
    private static Pattern pattern;
    static{
        pattern = Pattern.compile(TARGET_REGEX);
    }
    public static void main(String[] args){
        String targetUrl = "http://www.example.com";
        if (pattern.matcher(targetUrl).matches()){
            System.out.println("Matched");
        }else{
            System.out.println("Not Matched");
        }
    }
}