import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.printf("Result: %d", executeCommand("ls"));
    }

    private static int executeCommand(String command) {
        return Runtime.getRuntime().exec(command).waitFor();
    }
}