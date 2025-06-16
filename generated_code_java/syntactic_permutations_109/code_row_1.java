import java.io.*;  

public class UserInfo {  
    public static void main(String[] args) throws IOException {  
        String username = null;  
        if (args.length < 1) {  
            System.out.println("Enter a valid username");  
            return;  
        } else {  
            username = args[0];  
            executeCommand(username);  
        }  
    }  

    private static void executeCommand(String command) throws IOException {  
        ProcessBuilder processBuilder = new ProcessBuilder();  
        processBuilder.command("cat", "/etc/passwd");  
        processBuilder.redirectErrorStream(true);  
        Process process = processBuilder.start();  
        InputStream is = process.getInputStream();  
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));  
        String line;  
        while ((line = reader.readLine()) != null) {  
            System.out.println(line);  
        }  
    }  
}