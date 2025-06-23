import java.lang.annotation.*;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface Decorator{
    String url();
}

public class UrlMapping {
    
    private static final Map<String, Object> MAP = new HashMap<>();
    
    public static void map(String url, Object object){
        MAP.put(url, object);
    }
    
    public static Object getMappedObject(String url){
        return MAP.getOrDefault(url, () -> "No mapping found");
    }
}

public class Hello {
    private String username;

    public Hello(String username) {
        this.username = username;
    }
    
    public String hello() {
        return "Hello " + escape(this.username);
    }
    
    private static final Pattern AMPERSAND = Pattern.compile("&");
    private static final Pattern LESSTHAN = Pattern.compile("<");
    private static final Pattern GREATERTHAN = Pattern.compile(">");
    private static final Pattern QUOTE = Pattern.compile("\"");
    private static final Pattern SINGLEQUOTE = Pattern.compile("'");
    
    public String escape(String input) {
        return AMPERSAND.matcher(LESSTHAN.matcher(GREATERTHAN.matcher(QUOTE.matcher(SINGLEQUOTE.matcher(input).replaceAll("&apos;")).replaceAll("&gt;")).replaceAll("&lt;")).replaceAll("&quot;")).replaceAll("&amp;");
    }
}

@Decorator(url = "/hello/{username}")
public class HelloWorld {
    
    public String hello() {
        return new Hello(Request.getPathParameter("username")).hello();
    }
    
}

class Request {
    private static final Map<String, String> PATH_PARAMETERS = new HashMap<>();
    
    public static void setPathParameters(Map<String, String> pathParameters){
        PATH_PARAMETERS.putAll(pathParameters);
    }
    
    public static String getPathParameter(String key){
        return PATH_PARAMETERS.getOrDefault(key, "");
    }
}