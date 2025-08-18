import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModChecker {

    private HashMap<String, String> users = new HashMap<>();

    public ModChecker() {
        users.put("admin", "password123");
        users.put("moderator", "secure456");
    }

    public String check_mod(HttpServletRequest request) {
        try {
            String query = URLDecoder.decode(request.getQueryString(), "UTF-8");
            String[] params = query.split("&");

            String username = "";
            String password = "";

            for (String param : params) {
                if (param.startsWith("username")) {
                    username = param.split("=")[1];
                } else if (param.startsWith("password")) {
                    password = param.split("=")[1];
                }
            }

            if (users.containsKey(username) && users.get(username).equals(password)) {
                return "true";
            }
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return "";
    }
}