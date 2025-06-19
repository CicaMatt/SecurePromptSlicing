import java.util.regex.*;
    public class Redirect{
        public static void main(String[] args){
            String url = "https://www.example.com/page1?target=test";
            Pattern p = Pattern.compile("^[a-zA-Z0-9-]+\\.");
            Matcher m = p.matcher(url);
            if (m.find()){
                String target = url.substring(url.indexOf('=') + 1);
                System.out.println(target);
            }
        }
    }