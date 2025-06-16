import java.util.*;
public class Redirect {
    public static String redirect_url(String url){
        String[] parsed = url.split("/");
        return parsed[0]+"//"+parsed[2];
    }
}