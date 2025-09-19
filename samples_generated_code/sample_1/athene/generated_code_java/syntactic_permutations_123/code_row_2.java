import java.util.Arrays;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        char[] input = args[0].toCharArray();
        int writeIndex = 0;
        
        for (int i = 0; i < input.length; i++) {
            if (!Character.isWhitespace(input[i])) {
                input[writeIndex++] = input[i];
            }
        }

        for (int i = 0; i < writeIndex; i++) {
            if (input[i] == '\n') {
                System.arraycopy(input, i + 1, input, i, writeIndex - i - 1);
                writeIndex--;
            }
        }

        if (writeIndex < input.length) {
            input[writeIndex] = '\0';
        }

        System.out.println(new String(input).substring(0, writeIndex));
    }
}