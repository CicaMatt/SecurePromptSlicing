import java.util.regex.*;

public class Redirect {
     public static void main(String[] args) {
          String pattern = "^[a-zA-Z0-9-]+\\.";
          Pattern r = Pattern.compile(pattern);
          Matcher m = r.matcher(args[0]);
          if (m.find()) {
               String target = args[1];
               System.out.println("Redirecting to " + target);
          } else {
               System.out.println("Invalid url");
          }
     }
}