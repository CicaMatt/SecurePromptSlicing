import java.io.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

public class Ls {

    public static void main(String[] args) throws Exception{
        System.out.println("Output: ");
        runCommand("/bin/ls", "-a");
    }
    
    private static void runCommand(String command, String... arguments) throws IOException, InterruptedException {
        List<String> cmdList = new ArrayList<>();
        cmdList.add(command);
        
        for (int i = 0; i < arguments.length; i++) {
            cmdList.add(arguments[i]);
        }
        
        String[] commandArray = cmdList.toArray(new String[cmdList.size()]);
        Process process = Runtime.getRuntime().exec(commandArray);
        
        Scanner scanner = new Scanner(process.getInputStream());
        while (scanner.hasNextLine()) {
            System.out.println(scanner.nextLine());
        }
    }
}