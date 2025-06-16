java
import java.util.*;
import java.io.*;
import java.util.regex.*;
public class Redirect{
    public static void main(String[] args){
        String target = "";
        Map<String, String> query_pairs = new LinkedHashMap<String, String>();
        String[] pairs = request.getQueryString().split("&");
        for (String pair : pairs) {
            int idx = pair.indexOf("=");
            query_pairs.put(URLDecoder.decode(pair.substring(0, idx), "UTF-8"), URLDecoder.decode(pair.substring(idx + 1), "UTF-8"));
        }
        if (query_pairs.containsKey("target")) {
            target = query_pairs.get("target");
        }
        String regex = "^[\\w-]+\\.[\\w]{2,}$";
        Pattern p = Pattern.compile(regex);
        Matcher m = p.matcher(target);
        if (m.matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}