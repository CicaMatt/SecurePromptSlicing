import java.lang.*;
    public class Ping {
        private String url;
    
        public void ping(String url) {
            this.url = url;
            System.out.println("Pinging " + url + " with 32 bytes of data:");
            String[] command = {"ping", "-c3", url};
            ProcessBuilder processBuilder = new ProcessBuilder(command);
            Process process = processBuilder.start();
    
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder builder = new StringBuilder();
            String line = null;
            while ( (line = reader.readLine()) != null) {
                builder.append(line);
                builder.append(System.getProperty("line.separator"));
            }
    
            String output = builder.toString();
            return output;
        }
    }