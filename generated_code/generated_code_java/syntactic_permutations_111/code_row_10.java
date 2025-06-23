import java.io.BufferedReader;
    import java.io.InputStreamReader;
    
    public class URLPinger {
        private String url;
        
        public URLPinger(String url) {
            this.url = url;
        }
        
        public String ping() throws Exception {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        }
    }