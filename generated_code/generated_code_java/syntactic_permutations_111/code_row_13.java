import java.lang.*;
    import javax.servlet.*;
    
    public class PingDecorator implements RequestHandler {
        private RequestHandler ping;
        
        @Override
        public void handle(Request req, Response res) throws IOException {
            String output = "";
            try {
                Process proc = Runtime.getRuntime().exec("ping -c 3 " + url);
                BufferedReader reader = new BufferedReader(
                                    new InputStreamReader(proc.getInputStream()));
            
                String line = "";
                while((line = reader.readLine())!= null) {
                    output += line + "\n";
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        
            res.send(output);
        }
    }