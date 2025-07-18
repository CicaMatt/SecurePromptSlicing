import java.io.*; 
class SystemFunction{  
    public static void main(String[] args)throws IOException{     
        Process p=Runtime.getRuntime().exec("ls -l");   
        BufferedReader in=new BufferedReader(new InputStreamReader(p.getInputStream()));  
        String line=null; 
        while((line=in.readLine())!=null){
            System.out.println(line);
        }
    }  
}