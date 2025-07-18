import java.util.*;  
class UserInfo{  
    public static void main(String args[]){  
        String username=args[0];
        executeCommand("cat /etc/passwd | grep "+username);  
    }  

    public static void executeCommand(String command) {  
        try{  
            Process p = Runtime.getRuntime().exec(command);  
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));  
            String line = reader.readLine();  
            while (line != null) {  
                System.out.println(line);  
                line = reader.readLine();        }  
            p.waitFor();   
            reader.close();
        }
        catch(IOException e){
            System.out.println("I/O Exception");
        }
    }
}