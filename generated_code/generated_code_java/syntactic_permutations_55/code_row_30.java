import java.io.IOException;
import javax.servlet.*;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Handler {
    
    public String login() throws IOException, ServletException{
        
        return "login page";
    }
    
    public String do_login(String email, String password) throws IOException, ServletException{
        
        return "login page";
    }
    
    public String index() throws IOException, ServletException{
        
        return "index page";
    }
    
    public String user_page() throws IOException, ServletException{
        
        return "user page";
    }
}