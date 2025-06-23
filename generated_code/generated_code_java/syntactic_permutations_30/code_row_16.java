import java.util.regex.*; 
import javax.servlet.http.HttpServletRequest; 
import javax.servlet.http.HttpServletResponse; 
import java.io.IOException; 

public class Redirect { 
    public static void redirect(HttpServletRequest request, HttpServletResponse response) throws IOException { 
        String target = request.getParameter("target"); 
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9\\-]+\\.([a-zA-Z]{2,})"); 
        Matcher matcher = pattern.matcher(target); 
        if (matcher.find()) { 
            response.sendRedirect(target); 
        } else { 
            response.sendRedirect("/"); 
        } 
    } 
}