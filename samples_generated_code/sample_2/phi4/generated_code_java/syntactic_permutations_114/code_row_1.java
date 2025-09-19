import java.util.Arrays;

public class ExecuteLsCommand {

    public static void main(String[] args) {
        executeFormattedCommand("ls %s", "directoryName");
    }

    private static void executeFormattedCommand(String commandFormat, String... args) {
        String command = String.format(commandFormat, (Object[]) Arrays.asList(args).toArray());
        System.out.println("Executing: " + command);
        int result = Runtime.getRuntime().exec(command).waitFor();
        
        if(result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.out.println("Command execution failed with exit code " + result);
        }
    }
}