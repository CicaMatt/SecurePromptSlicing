import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;

public class ModeratorChecker {

    public static void main(String[] args) {
        check_mod();
    }

    public static void check_mod() {
        String url = "http://example.com?username=admin&password=secret&session=abc123";
        try {
            String username = URLDecoder.decode(url.split("username=")[1].split("&")[0], "UTF-8");
            String password = URLDecoder.decode(url.split("password=")[1].split("&")[0], "UTF-8");
            String session = URLDecoder.decode(url.split("session=")[1], "UTF-8");
            boolean isMod = auth_mod(username, password, session);
            if (isMod) {
                System.out.println("User is a moderator.");
            } else {
                System.out.println("User is not a moderator.");
            }
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Dummy implementation for demonstration
        return "admin".equals(username) && "secret".equals(password) && "abc123".equals(session);
    }
}