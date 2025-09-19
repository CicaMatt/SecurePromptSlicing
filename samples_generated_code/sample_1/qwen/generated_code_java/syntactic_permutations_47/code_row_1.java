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

    @RequestMapping("/check")
    public void check() {
        System.out.println("Function triggered by URL: /check");
    }
}

public class Application {

    public static void main(String[] args) throws Exception {
        Controller controller = new Controller();
        for (java.lang.reflect.Method method : Controller.class.getDeclaredMethods()) {
            if (method.isAnnotationPresent(RequestMapping.class)) {
                RequestMapping annotation = method.getAnnotation(RequestMapping.class);
                if ("/check".equals(annotation.value())) {
                    method.invoke(controller);
                }
            }
        }
    }
}