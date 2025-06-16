import java.io.BufferedReader;
    import java.io.InputStreamReader;
    
    public class Ping {
      private String url;
     
        public String getUrl() { return url; }
        public void setUrl(String value) { url = value; }
     
        public Ping(String url){
            this.url=url;
        }
     
        public String ping(){
            String pong;
            try {
                ProcessBuilder pb = new ProcessBuilder("ping", url);
                Process process = pb.start();
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
     
                String line = null;
                while ((line = reader.readLine()) != null) {
                    pong += line + "\n";
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            if(pong == null){
                return "The URL is not alive.";
            }
            else{
                return "The URL is alive.";
            }
        }
    }