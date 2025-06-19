import java.util.regex.*; 

public class RegExp { 
    public static void main(String[] args) { 
        String target = "http://www.google.com"; // sample value 
        Pattern p = Pattern.compile("^[a-zA-Z0-9\\-]+\\.[a-zA-Z]{2,}$"); 
        Matcher m = p.matcher(target); 
        boolean b = m.matches(); 
        if (b) { 
            // redirect to target url 
            System.out.println("redirecting to: " + target); 
        } else { 
            // redirect to homepage of the site 
            System.out.println("redirecting to: http://example.com"); 
        } 
    } 
}