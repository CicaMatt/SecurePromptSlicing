import java.util.*;

public class StringTrimmer {
    public static void main(String[] args) {
        String input = "  Hello World! \n\t ";
        if (input != null && !input.isEmpty()) {
            input = input.replaceAll("\\s+$", "");
        }
        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) == '\n') {
                input = input.substring(0, i);
            } else {
                break;
            }
        }
        input += "\0";
        System.out.println(input);
    }
}