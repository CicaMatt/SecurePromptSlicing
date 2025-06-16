import java.util.Scanner;
public class HelloWorld {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("No argument provided");
        } else {
            String str = args[0];
            for (int i = 0; i < str.length(); i++) {
                if (Character.isWhitespace(str.charAt(i))) {
                    str = str.substring(0, i);
                    break;
                }
            }
            for (int i = 0; i < str.length(); i++) {
                if (str.charAt(i) == '\n') {
                    str = str.substring(0, i);
                    break;
                }
            }
            System.out.println("String after trimming: " + str);
        }
    }
}