import java.util.regex.*;

    public class Redirect {
        private static final String REGEX = "^[\\w-]+\\.[\\w]+$";
        private static Pattern pattern = Pattern.compile(REGEX);

        public static void main(String[] args) throws Exception {
            String target = "https://www.example.com/target?param1=value&param2=value";
            
            if (pattern.matcher(target).matches()){
                System.out.println("Redirecting to: " + target);
            } else {
                System.out.println("Redirecting to: https://www.example.com");
            }
        }
    }