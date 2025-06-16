import java.io.*; 
import java.util.*; 
public class Main {
    public static void main(String[] args) throws IOException{
        ProcessBuilder pb = new ProcessBuilder("id",args[0]);
        Process process = pb.start();
        int exitCode = process.waitFor();
        if (exitCode == 0){
            BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line = null;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        }else{
            BufferedReader br = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            String line = null;
            while ((line = br.readLine()) != null) {
                System.err.println(line);
            }
        }
    }
}