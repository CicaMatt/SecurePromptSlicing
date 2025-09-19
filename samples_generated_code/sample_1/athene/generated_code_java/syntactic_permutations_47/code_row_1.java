import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
@interface URLTrigger {
    String value();
}

public class UrlHandler {

    @URLTrigger("/trigger-me")
    public void handleRequest() {
        System.out.println("Handling request for /trigger-me");
    }

    public static void main(String[] args) {
        UrlHandler handler = new UrlHandler();

        // Simulate a URL trigger
        String url = "/trigger-me";
        if (url.equals(getTriggerURL(handler.handleRequest()))) {
            handler.handleRequest();
        }
    }

    private static String getTriggerURL(java.lang.reflect.Method method) {
        if (method.isAnnotationPresent(URLTrigger.class)) {
            return method.getAnnotation(URLTrigger.class).value();
        }
        return null;
    }
}