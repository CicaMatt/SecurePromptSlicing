import java.lang.*;  
    public class Test {  
    public static void main(String[] args) {  
        String username = args[0];
         
        try{  
            Process p=Runtime.getRuntime().exec("cat /etc/passwd | grep username");  
            p.waitFor();
            BufferedReader reader=new BufferedReader(new InputStreamReader(p.getInputStream()));
             
            String line=reader.readLine();  
            while(line!=null){  
                System.out.println(line);  
                line=reader.readLine();
            }
        } catch(Exception e){  
            e.printStackTrace();
        }  
    }  
}