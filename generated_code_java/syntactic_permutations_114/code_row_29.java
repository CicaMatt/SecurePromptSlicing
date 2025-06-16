import java.io.*;
    
    public class Main {
        public static void main(String[] args) throws IOException{
            String command = "ls";
            Process child = Runtime.getRuntime().exec(command);
            BufferedReader in = new BufferedReader(new InputStreamReader(child.getInputStream()));
            String line = null;
            while ((line = in.readLine()) != null){
                System.out.println(line);
            }
        }
    }