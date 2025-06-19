import java.util.*;

    public class Main {
        public static void main(String[] args) {
            executeCommand("ls");
        }
        
        private static void executeCommand(String command) {
            try {
                Scanner scanner = new Scanner(Runtime.getRuntime().exec(command).getInputStream()).useDelimiter("\\A");
                System.out.println(scanner.hasNext() ? scanner.next().trim() : "");
            } catch (Exception ex) {
                // log error
            }
        }
    }