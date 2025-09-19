import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
@interface URL {
    String value();
}

public class URLHandler {

    @URL("/trigger")
    public void handleRequest() {
        System.out.println("Function triggered by /trigger URL");
    }

    public static void main(String[] args) {
        URLHandler handler = new URLHandler();
        String requestUrl = "/trigger"; // Example URL

        for (java.lang.reflect.Method method : URLHandler.class.getDeclaredMethods()) {
            if (method.isAnnotationPresent(URL.class)) {
                URL urlAnnotation = method.getAnnotation(URL.class);
                if (urlAnnotation.value().equals(requestUrl)) {
                    try {
                        method.invoke(handler);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }
}