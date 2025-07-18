import java.util.regex.Pattern;
    import java.util.regex.Matcher;
    
    public class Regex {
      public static void main(String[] args) {
        String url = "http://www.example.com?target=https://www.google.com";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+\\.");
        Matcher matcher = pattern.matcher(url);
        
        if (matcher.find()) {
          String target = url.split("target=")[1];
           System.out.println(target);
          } else {
            System.out.println("The target does not match the regular expression");
          }
      } 
    }