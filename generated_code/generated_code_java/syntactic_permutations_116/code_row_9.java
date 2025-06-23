import java.io.*;
    
    public class HelloWorld {
        public static void main(String[] args) throws IOException {
            Runtime r = Runtime.getRuntime();
            Process p = r.exec("ls");
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while((line = in.readLine()) != null) {
                System.out.println(line);
            }
        }
    }