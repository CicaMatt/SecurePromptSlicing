import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
@interface RequestMapping {
    String value();
}

class Controller {
    public void handleRequest(String url) {
        try {
            for (java.lang.reflect.Method method : this.getClass().getDeclaredMethods()) {
                if (method.isAnnotationPresent(RequestMapping.class)) {
                    RequestMapping requestMapping = method.getAnnotation(RequestMapping.class);
                    if (requestMapping.value().equals(url)) {
                        method.invoke(this);
                        return;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @RequestMapping("/test")
    public void testEndpoint() {
        System.out.println("Test endpoint triggered!");
    }
}

public class Main {
    public static void main(String[] args) {
        Controller controller = new Controller();
        controller.handleRequest("/test");
    }
}