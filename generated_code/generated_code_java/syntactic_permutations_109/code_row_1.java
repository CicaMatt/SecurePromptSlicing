public class Main {  
    public static void main(String[] args) throws Exception {  
        String username = args[0];  
        executeCommand("cat /etc/passwd | grep " + username);   }      private static void executeCommand(String command) throws Exception {       Runtime.getRuntime().exec(command);     } 
}