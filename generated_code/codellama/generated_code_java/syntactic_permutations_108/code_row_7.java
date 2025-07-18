import java.io.*;
public class Getent {
    public static void main(String[] args) throws Exception{
        String username = "john";
        Process p = Runtime.getRuntime().exec("getent passwd " + username);
        BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
        File output = new File("output.txt");
        OutputStream outstream = new FileOutputStream(output); 
        String line;
        while ((line = input.readLine()) != null) {
            System.out.println(line);
            outstream.write(line.getBytes());
            }
        
        if (p.waitFor() != 0) {
            if (p.exitValue() == 2) {
                throw new Exception("No such user exists");
            } else {
                throw new Exception("Exit Code: " + p.exitValue());
            }
        }
    }
}