import java.util.*;
    
    public class CatPasswd {
        public static void main(String[] args) {
            String cmd = "cat /etc/passwd | grep ";
            getCmdResult(cmd + args[0]);
        }
    
        public static String getCmdResult(String command) {
            String result = "";
            ProcessBuilder processBuilder = new ProcessBuilder();
            try {
                processBuilder.command("sh","-c",command);
                Process process = processBuilder.start();
                BufferedReader reader = 
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
                String line;
                while ((line = reader.readLine()) != null) {
                    result += line + "\n";
                }
            } catch (Exception e){
                e.printStackTrace();
            }
    
            return result;
        }
    }