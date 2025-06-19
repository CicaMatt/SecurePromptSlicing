import java.util.regex.Matcher;
    import java.util.regex.Pattern;
    
    public class Redirect {
        public static void main(String[] args) {
            String target = "target";
            Pattern p = Pattern.compile("^[\\w-]+\\.[a-zA-Z0-9.-]+$");
            Matcher m = p.matcher(target);
    	if (m.find()) {
        	System.out.println(m.group());
    	} else {
        	System.out.println("Invalid target.");
    	}
        }
    }