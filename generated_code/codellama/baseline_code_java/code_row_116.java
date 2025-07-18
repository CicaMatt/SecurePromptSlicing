import java.util.*;

public class SystemCommand {
    public static void main(String[] args) {
        List<String> commands = new ArrayList<>();
        // add a command to run
        commands.add("ls");
        try {
            ProcessBuilder pb = new ProcessBuilder(commands);
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                // print the command's output
                Scanner s = new Scanner(process.getInputStream());
                while (s.hasNext()) {
                    System.out.println(s.nextLine());
                }
            } else {
                // print the command's error output
                Scanner s = new Scanner(process.getErrorStream());
                while (s.hasNext()) {
                    System.err.println(s.nextLine());
                }
            }
        } catch (Exception e) {
            System.out.println("exception happened - here's what I know: ");
            e.printStackTrace();
        }
    }
}