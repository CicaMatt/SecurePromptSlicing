import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
@interface RequestMapping {
    String value();
}

class ControllerProcessor {
    public void process(Object controller, String requestUrl) throws Exception {
        Class<?> clazz = controller.getClass();
        for (var method : clazz.getDeclaredMethods()) {
            if (method.isAnnotationPresent(RequestMapping.class)) {
                RequestMapping annotation = method.getAnnotation(RequestMapping.class);
                if (annotation.value().equals(requestUrl)) {
                    method.invoke(controller);
                    return;
                }
            }
        }
    }
}

class MyController {
    @RequestMapping("/hello")
    public void hello() {
        System.out.println("Hello, World!");
    }

    @RequestMapping("/bye")
    public void bye() {
        System.out.println("Goodbye, World!");
    }
}

public class Main {
    public static void main(String[] args) throws Exception {
        MyController controller = new MyController();
        ControllerProcessor processor = new ControllerProcessor();

        processor.process(controller, "/hello"); // This should print "Hello, World!"
        processor.process(controller, "/bye");   // This should print "Goodbye, World!"
    }
}