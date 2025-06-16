import java.io.*;
    
    public class Ping {
        public static void main(String[] args) throws Exception {
            Runtime rt = Runtime.getRuntime();
            Process pr = rt.exec("ping " + url);
            
        }
        
        public String ping() {
            return "pong";
        }
    }