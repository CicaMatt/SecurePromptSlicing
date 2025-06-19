import java.util.*;

    public class Main {
        public static void main(String[] args) {
            String str = "ls -l";
            executeCmd(str);
        }
    
        private static void executeCmd(String cmd) {
            try {
                Process proc = Runtime.getRuntime().exec(cmd);
                BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
                String line;
                while((line = reader.readLine()) != null){
                    System.out.println(line);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    
    }