import java.util.*;

public class StringTrimmer {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        
        if (input != null && !input.isEmpty()) {
            input = input.replaceAll("\\s+$", "");
        }
        
        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == '\n') {
                input = input.substring(0, i).trim();
                break;
            }
        }

        input = input + "\0";
        
        System.out.println(input);
    }
}