import java.util.regex.*;
import javax.servlet.http.HttpServletResponse;

public class Redirect {

    private static final Pattern PATTERN = Pattern.compile("^[A-Za-z0-9\\-]+\\.");

    public static void main(String[] args) {
        String target = "https://www.google.com";
        HttpServletResponse response = new HttpServletResponse();
        boolean matches = PATTERN.matcher(target).matches();
        if (matches){
            response.sendRedirect(target);
        }else{
            response.sendRedirect("/");
        }
    }
}