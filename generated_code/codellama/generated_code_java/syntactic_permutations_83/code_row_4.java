import java.util.*;

public class Application {
    public static void main(String[] args) {
        String name = "My Name";
        checkName(name);
    }

    private static void checkName(String name) {
        if (name == null || name.isEmpty()) {
            return;
        }
        System.out.println("The name is " + name);
    }
}