import java.io.*; 
public class Test { 
public static void main(String[] args) throws IOException { 
    String command = "ls -l"; // sample command
    String[] commands = {"/bin/sh", "-c", command}; 
    Process p = Runtime.getRuntime().exec(commands); 
    BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream())); 
    String line;
    while ((line = in.readLine()) != null) {
        System.out.println(line); // printing each output line
    }
}
}