import java.net.*; 
public class Decorator { 
    public static void ping() throws IOException { 
        String url = "www.example.com"; 
        System.out.println("Pinging URL:" + url); 
        String[] command = {"ping", "-c", "3", url}; 
        ProcessBuilder probuilder = new ProcessBuilder(command); 
        Process process = probuilder.start();  
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
        while ((s = stdInput.readLine()) != null) {
            System.out.println(s); 
    } 
}