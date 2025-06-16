import java.util.Scanner;

public class Ls {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a string : ");
        String str = sc.nextLine();
        executeCommand(str);
    }

    private static void executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder(command);
        try {
            Process process = processBuilder.start();
            Scanner input = new Scanner(process.getInputStream());
            while (input.hasNext()) {
                String line = input.nextLine();
                System.out.println(line);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}