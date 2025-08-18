import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", Arrays.toString(args).replace("[", "").replace("]", "").replace(", ", " "));
        try {
            Process p = Runtime.getRuntime().exec(command);
            p.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}