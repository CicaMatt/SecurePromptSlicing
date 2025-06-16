import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            String command = "ls";
            System.out.print("Command: %s\n", command);
            int status = system(command);
            System.out.print("Return code: %d\n", status);
        }
    }