import java.io.*;  

    public class Main {  
        public static void main(String[] args) throws IOException {  
            String userName = args[0];  
            String command = "cat /etc/passwd | grep "+userName;  
            executeCommand(command);  
        }  

    private static void executeCommand(String command) {  
        Process process = Runtime.getRuntime().exec(command);  
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));  
        String line;  
        while ((line = reader.readLine()) != null) {  
            System.out.println(line);  
        }  
    }
}