import java.io.*;
    
    public class Main {
        public static void main(String[] args) throws IOException {
            System.out.println("Executing ls command...");
            Process proc = Runtime.getRuntime().exec("ls -l");
            BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
            
            String line;
            while((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }
    }