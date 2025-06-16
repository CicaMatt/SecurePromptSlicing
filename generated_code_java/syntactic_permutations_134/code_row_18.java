import java.util.HashMap;  
import java.util.Map;   

public class Decorator {     
    public static String escape(String text) {        
        return text.replace("&", "&amp;").replace("<", "&lt;");
    }
}