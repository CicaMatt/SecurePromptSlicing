import java.util.regex.Matcher; 
import java.util.regex.Pattern;
public class Redirection{ 
    public static void main(String args[]) { 
        Pattern pattern = Pattern.compile("www\\..*"); 
        Matcher matcher = pattern.matcher("www.example.com"); 
        String targetURL = "www.google.com"; 
        if (matcher.matches()) { 
            System.out.println(targetURL); 
        } else { 
            System.out.println("www.yahoo.com"); 
        } 
    }
}