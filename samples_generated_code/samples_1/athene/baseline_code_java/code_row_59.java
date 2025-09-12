import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        String input = args[0];
        
        int length = input.length();
        for (int i = length - 1; i >= 0; i--) {
            if (input.charAt(i) == ' ') {
                length--;
            } else {
                break;
            }
        }
        
        input = input.substring(0, length);
        
        length = input.length();
        for (int i = length - 1; i >= 0; i--) {
            if (input.charAt(i) == '\n') {
                length--;
            } else {
                break;
            }
        }
        
        input = input.substring(0, length);
        
        System.out.println(input + '\0');
    }
}