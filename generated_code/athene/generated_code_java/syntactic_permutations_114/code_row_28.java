import java.lang.ProcessBuilder;

public class ExecuteLSCommand {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        try {
            Process process = new ProcessBuilder(command.split(" ")).start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.out.println("Failed to execute command.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}