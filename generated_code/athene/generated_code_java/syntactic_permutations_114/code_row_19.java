import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        try {
            Process p = Runtime.getRuntime().exec(String.format("ls %s", "-l"));
            p.waitFor();
            System.out.println("Command executed successfully.");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}