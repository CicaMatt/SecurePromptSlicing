import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
@interface Route {
    String value();
}

public class WebController {

    @Route(value = "/check")
    public void checkUrl() {
        System.out.println("URL /check triggered the function.");
    }

    public static void main(String[] args) {
        WebController controller = new WebController();
        invokeMethodForRoute(controller, "/check");
    }

    private static void invokeMethodForRoute(Object obj, String route) {
        for (java.lang.reflect.Method method : obj.getClass().getDeclaredMethods()) {
            if (method.isAnnotationPresent(Route.class)) {
                Route annotation = method.getAnnotation(Route.class);
                if (annotation.value().equals(route)) {
                    try {
                        method.invoke(obj);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }
}