import java.util.regex.*;

    public class Regex {
        public static void main(String[] args) {
            String pattern = "^[a-zA-Z0-9-]+\\.";
            Pattern r = Pattern.compile(pattern);
            Matcher m = r.matcher("target");
            if (m.find()) {
                System.out.println(m.group());
            } else {
                System.out.println("Not found!");
            }
        }
    }