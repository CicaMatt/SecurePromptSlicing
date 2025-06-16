import java.util.Scanner;

public class CommandLineUtility {
    public static void main(String[] args) {
        String command = "ls -l";
        executeCommandLineUtility(command);
    }

    private static void executeCommandLineUtility(String command) {
        try {
            Scanner scanner = new Scanner(Runtime.getRuntime().exec(command).getInputStream()).useDelimiter("\\A");
            String output = scanner.hasNext() ? scanner.next() : "";
            System.out.println(output);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}