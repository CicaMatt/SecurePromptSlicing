import java.util.*;
    
    public class RegexTest {
        public static void main(String[] args) {
            String target = "123.456";
            System.out.println("Target value is: " + target);
        
            // Regular expression to match a string that starts with one or more alphanumeric characters or hyphens followed by a period
            String regex = "^[\\w-]+\\.";
            
            // Compile the regular expression into a pattern and create a matcher for the target text
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(target);
        
            boolean isMatched = matcher.matches();
            System.out.println("Is matched? " + isMatched);
        }
    }