import java.io.*;  
    public class ExecuteLsCommand {  
        public static void main(String[] args) throws IOException {  
            String s;  
            Process p = Runtime.getRuntime().exec("ls");  
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));  
            while ((s = br.readLine()) != null)  
                System.out.println(s);  
        }  
    }