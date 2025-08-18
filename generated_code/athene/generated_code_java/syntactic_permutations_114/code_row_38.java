import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", Arrays.toString(args).replaceAll("[\\[\\]]", ""));
        Runtime.getRuntime().exec(command);
    }
}