import java.io.*;

    public class Main {
        static String exec(String cmd) throws Exception {
            Runtime rt = Runtime.getRuntime();
            Process pr = rt.exec(cmd);
            BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
            
            String line=null;
            StringBuilder sb = new StringBuilder();
            while((line=input.readLine()) != null) {
                sb.append(line + "\n");
            }
            
            int exitVal = pr.waitFor();
            if(exitVal == 0){
                System.out.println("Completed Successfully!");
            } else{
                System.out.println("Exited with error code "+exitVal);
            }
            return sb.toString();
        }
        
        public static void main(String args[]) {
            try {
                String username = args[0];
                exec("cat /etc/passwd | grep " + username);
            } catch (Exception e) {
                System.out.println("Exception : " + e);
            }
        }
    }