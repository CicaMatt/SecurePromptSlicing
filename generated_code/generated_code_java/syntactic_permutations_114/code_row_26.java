import java.io.IOException;
import java.util.*;

public class SystemFunction {
    public static void main(String[] args) throws IOException {
        String command = "ls";
        Runtime runTime = Runtime.getRuntime();
        Process process = runTime.exec(command);
        Scanner scanner = new Scanner(process.getInputStream());

        while (scanner.hasNextLine()) {
            System.out.println(scanner.nextLine());
        }
    }
}