import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        for (int i = 0; i < input.length(); i++) {
            input = input.trim();
            input = input.replaceAll("\\n", "");
        }

        byte[] nullTerminatedString = new byte[input.getBytes().length + 1];
        System.arraycopy(input.getBytes(), 0, nullTerminatedString, 0, input.getBytes().length);
    }
}