import java.util.regex.*;
    
    public class Redirect {
        public static void main(String[] args) {
            String target = "https://www.example.com";
            Pattern pattern = Pattern.compile("^[\\w-]+\\.[a-zA-Z]{2,}[\\w.:?&//=~#-]*$");
            Matcher matcher = pattern.matcher(target);
            if (matcher.matches()) {
                System.out.println("Valid URL!");
            } else {
                System.out.println("Invalid URL!");
            }
        }
    }