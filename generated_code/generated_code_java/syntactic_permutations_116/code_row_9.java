import java.util.Scanner;

public class SystemFunction {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String lsCommand = "ls -l";
        String commandOutput = "";
        try {
            Process p = Runtime.getRuntime().exec(lsCommand);
            Scanner scanner = new Scanner(p.getInputStream());
            while (scanner.hasNextLine()) {
                commandOutput += scanner.nextLine() + "\n";
            }
            System.out.println("Command output: " + commandOutput);
        } catch (IOException e) {
            System.err.println(e);
        }
    }
}