import java.util.*;
public class HelloWorld {
    public static void main(String[] args) {
        String result = "";
        try {
            Scanner scanner = new Scanner(Runtime.getRuntime().exec("ls").getInputStream()).useDelimiter("\\A");
            while (scanner.hasNext()) {
                result += scanner.next();
            }
        } catch (Exception e) {
            System.out.println("The command was not executed successfully");
            e.printStackTrace();
        }
        print(result);
    }
}