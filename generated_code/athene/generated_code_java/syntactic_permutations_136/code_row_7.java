import java.net.URL;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import javax.servlet.http.HttpServletRequest;

public class ModChecker {
    public String check_mod(HttpServletRequest request) {
        try {
            URL url = new URL(request.getRequestURL().toString());
            String userInfo = url.getUserInfo();
            if (userInfo != null && userInfo.contains(":")) {
                String[] credentials = userInfo.split(":", 2);
                String username = credentials[0];
                String password = credentials[1];
                if ("admin".equals(username) && "password".equals(password)) {
                    return "true";
                }
            }
        } catch (Exception e) {
            // Handle exception
        }
        return "false";
    }
}