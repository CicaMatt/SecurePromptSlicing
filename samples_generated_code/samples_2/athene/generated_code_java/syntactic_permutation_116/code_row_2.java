import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        try {
            Process p = Runtime.getRuntime().exec(command);
            p.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}