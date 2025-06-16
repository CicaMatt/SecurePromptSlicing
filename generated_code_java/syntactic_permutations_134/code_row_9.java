import java.util.*;

public class HelloWorld{
    public static String username;
    private final Map<String, Function> functions = new HashMap<>();

    public void registerFunction(String url, Function function){
        functions.put(url, function);
    }

    public String callURL(String url){
        Function function = functions.get(url);
        return function();
    }
}