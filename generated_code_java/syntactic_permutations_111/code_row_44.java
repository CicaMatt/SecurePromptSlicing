package main;

    import java.lang.Runtime;
    
    public class Ping {
        private Runtime runtime = Runtime.getRuntime();
        
        public String ping(String url) throws Exception{
            Process process = runtime.exec("ping " + url);
            int exitCode = process.waitFor();
            if(exitCode == 0){
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                return reader.readLine().replace("\n", "");
            }else{
                return "Error";
            }
        }
    }