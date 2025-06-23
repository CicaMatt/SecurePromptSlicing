java
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Main {

    public static void main(String[] args) {
        String url = "http://www.example.com";
        String pattern = "^((ftp|http|https):\\/\\/)?(\\w+:{0,1}\\w*@)?(\\S+)(:[0-9]+)?(\\/|\\/([\\w#!:.?+=&%@!\\-\\/]))?$";
        String defaultURL = "http://www.example2.com";
        
        Pattern p = Pattern.compile(pattern);
        Matcher m = p.matcher(url);

        if (m.matches()) {
            System.out.println("Matched");
            //redirect to url;
        } else {
            System.out.println("Did not match");
            //redirect to defaultURL;
        }
    }
}