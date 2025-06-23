import java.io.*;
    import java.util.*;

    public class PingDecorator {
        private String url;
        
        public PingDecorator(String url) {
            this.url = url;
        }
        
        public void ping() {
            try {
                Process process = Runtime.getRuntime().exec("ping " + url);
                
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                
                String line;
                while ((line = reader.readLine()) != null) {
                    System.out.println(line);
                }
            
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }