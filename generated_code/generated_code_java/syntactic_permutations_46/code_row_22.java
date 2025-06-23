import java.io.*;

@Decorator("/img")
public class ImageDecorator {
    @FunctionalInterface
    interface Handler {
        String handle(String name);
    }

    public static void main(Handler handler) throws Exception {
        // ...
    }
}