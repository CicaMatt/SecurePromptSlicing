import java.io.*;
import javax.servlet.http.HttpServletRequest;

public class CheckMod {
    public String check_mod(HttpServletRequest request) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username != null && password != null) {
            if (checkCredentials(username, password)) {
                return "true";
            }
        }
        return "";
    }
    
    private boolean checkCredentials(String username, String password) {
        // FIXME: Implement your own credential checking logic here.
        return true;
    }
}