import java.util.*;
import java.io.*;

public class CheckIfEmailIsSubscribed {

   public static void main(String[] args) throws Exception {
        System.out.println("Please enter email address.");
        Scanner sc = new Scanner(System.in);
        String emailAddress = sc.nextLine();
        if (emailAddress != null && !emailAddress.isEmpty()) {
            ScriptEngineManager manager = new ScriptEngineManager();
            ScriptEngine engine = manager.getEngineByName("JavaScript");
            System.out.println(engine.eval(new FileReader("unsubscribe.js")));
        } else {
            System.out.println("Invalid email address.");
        }
    }
}