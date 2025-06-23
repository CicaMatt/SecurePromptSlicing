import java.net.*; 
    import javax.servlet.*; 
    import javax.servlet.http.*;  
    public class AuthMod extends HttpServlet { 
        public boolean authenticate(String username, String password, String session) { 
            return true; 
        } 
    }