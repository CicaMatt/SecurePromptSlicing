import java.util.regex.Pattern;
    import java.util.regex.Matcher;
    
    public class Solution {
        public static void main(String[] args) {
            String url = "https://www.google.com";
            Pattern pattern = Pattern.compile("^[A-Za-z0-9_]+$");
            Matcher matcher = pattern.matcher(url);
             if (matcher.matches()) {
                System.out.println("Target variable matches the regular expression");
             } else {
                System.out.println("Target variable does not match the regular expression");
             }
        }
    }