import java.io.*; 
    public class Main { 
        public static void main(String[] args) throws IOException{ 
            String command="ls"; 
            Process p=Runtime.getRuntime().exec(command); 
            BufferedReader br=new BufferedReader(new InputStreamReader(p.getInputStream())); 
            String line; 
            while((line=br.readLine())!=null){ 
                System.out.println(line); 
            } 
        } 
    }